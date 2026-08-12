/* Copyright (c) 2026 Arthur DAUZAT
 * SPDX-License-Identifier: BSD-3-Clause */

#include <stdarg.h>
#include <stdio.h>

#include <libcpmfs.h>
#include <libhxcfe.h>

#include "floppy.h"

static struct {
	HXCFE *hxcfe;
	HXCFE_FLOPPY *floppy;
	HXCFE_IMGLDR *loader;
	HXCFE_SECTORACCESS *sector_access;

	const struct disk_definition *def;
} ctx;

static int32_t hxcfe_print_cb(int32_t type, const char *string, ...)
{
	va_list marker;

	if (type != MSG_WARNING && type != MSG_ERROR)
		return 0;
	va_start(marker, string);

	vprintf(string, marker);
	printf("\n");

	va_end(marker);
	return 0;
}

static int get_index_for_id(uint32_t c, uint32_t h, int32_t s, int type)
{
	HXCFE_SECTCFG *sc;
	int i = 0;

	hxcfe_resetSearchTrackPosition(ctx.sector_access);
	do {
		sc = hxcfe_getNextSector(ctx.sector_access, c, h, type);
		if (sc) {
			if (i == s) {
				i = hxcfe_getSectorConfigSectorID(ctx.hxcfe, sc);
				hxcfe_freeSectorConfig(ctx.sector_access, sc);
				return i;
			}

			hxcfe_freeSectorConfig(ctx.sector_access, sc);
			i++;
		}
	} while (sc);
	return 0;
}

int read_sector(void *userdata, uint32_t c, uint32_t h, uint32_t s, uint8_t *out_s)
{
	int status;

	s = get_index_for_id(c, h, s, ctx.def->encoding);
	hxcfe_readSectorData(ctx.sector_access, c, h, s, 1,
			     ctx.def->attrs.sector_size, ctx.def->encoding,
			     out_s, &status);

	if (status == FDC_NOERROR)
		return 0;
	return -1;
}

int write_sector(void *userdata, uint32_t c, uint32_t h, uint32_t s, uint8_t *in_s)
{
	int status;

	s = get_index_for_id(c, h, s, ctx.def->encoding);
	hxcfe_writeSectorData(ctx.sector_access, c, h, s, 1,
			      ctx.def->attrs.sector_size, ctx.def->encoding,
			      in_s, &status);

	if (status == FDC_NOERROR)
		return 0;
	return -1;
}

int init_floppy(char *filename, const struct disk_definition *diskdef)
{
	int loader_id;
	int ret;

	if (!filename || !diskdef)
		return -1;

	ctx.def = diskdef;

	ctx.hxcfe = hxcfe_init();
	if (!ctx.hxcfe)
		return -1;
	ctx.loader = hxcfe_imgInitLoader(ctx.hxcfe);
	if (!ctx.loader)
		return -1;

	loader_id = hxcfe_imgAutoSetectLoader(ctx.loader, filename, 0);
	ctx.floppy = hxcfe_imgLoad(ctx.loader, filename, loader_id, &ret);
	if (!ctx.floppy || ret != 0)
		return -1;

	/* Set logging after autoselect+load as these functions generate many
	 * logs by trying to brute-force each format. */
	hxcfe_setOutputFunc(ctx.hxcfe, hxcfe_print_cb);

	ctx.sector_access = hxcfe_initSectorAccess(ctx.hxcfe, ctx.floppy);
	if (!ctx.sector_access)
		return -1;

	/* Some disks like Zorba ignore side ID */
	hxcfe_setSectorAccessFlags(ctx.sector_access, SECTORACCESS_IGNORE_SIDE_ID);

	return 0;
}

void destroy_floppy(void)
{
	hxcfe_deinitSectorAccess(ctx.sector_access);
	hxcfe_imgUnload(ctx.loader, ctx.floppy);
	hxcfe_imgDeInitLoader(ctx.loader);
	hxcfe_deinit(ctx.hxcfe);
}
