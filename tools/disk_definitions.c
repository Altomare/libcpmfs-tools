/* Copyright (c) 2026 Arthur DAUZAT
 * SPDX-License-Identifier: BSD-3-Clause */

#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include <libhxcfe.h>

#include "disk_definitions.h"


struct disk_definition micral_p2 = {
	.shortname = "micral_p2",
	.name = "Bull Micral P2",
	.attrs = {
		.cylinders = 76,
		.heads = 2,
		.sector_count = 16,
		.sector_size = 256,
		.block_size = 2048,
		.max_dir_entries = 256,
		.boot_cylinders = 3,
		.fill_order = CPM_FILL_NORMAL,
	},
	.encoding = ISOIBM_MFM_ENCODING,
};

static uint32_t otrona_attache_skew[10] = {1, 6, 2, 7, 3, 8, 4, 9, 5, 10};
struct disk_definition otrona_attache = {
	.shortname = "otrona_attache",
	.name = "Otrona Attache",
	.attrs = {
		.cylinders = 40,
		.heads = 2,
		.sector_count = 10,
		.sector_size = 512,
		.block_size = 2048,
		.max_dir_entries = 128,
		.skew_table = otrona_attache_skew,
		.boot_cylinders = 3,
		.fill_order = CPM_FILL_HCS,
	},
	.encoding = ISOIBM_MFM_ENCODING,
};

static uint32_t bondwell_12_skew[18] = {1, 10, 2, 11, 3, 12, 4, 13, 5, 14, 6, 15, 7, 16, 8, 17, 9, 18};
struct disk_definition bondwell_12 = {
	.shortname = "bondwell_12",
	.name = "Bondwell 12",
	.attrs = {
		.cylinders = 40,
		.heads = 1,
		.sector_count = 18,
		.sector_size = 256,
		.block_size = 2048,
		.max_dir_entries = 64,
		.skew_table = bondwell_12_skew,
		.boot_cylinders = 2,
		.fill_order = CPM_FILL_NORMAL,
	},
	.encoding = ISOIBM_MFM_ENCODING,
};

static uint32_t osborne_1_skew[10] = {1, 6, 2, 7, 3, 8, 4, 9, 5, 10};
struct disk_definition osborne_1 = {
	.shortname = "osborne_1",
	.name = "Osborne 1",
	.attrs = {
		.cylinders = 40,
		.heads = 1,
		.sector_count = 10,
		.sector_size = 256,
		.block_size = 2048,
		.max_dir_entries = 64,
		.skew_table = osborne_1_skew,
		.boot_cylinders = 3,
		.fill_order = CPM_FILL_NORMAL,
	},
	.encoding = ISOIBM_FM_ENCODING,
};

static uint32_t epson_qx10_skew[10] = {1, 8, 5, 2, 9, 6, 3, 10, 7, 4};
struct disk_definition epson_qx10 = {
	.shortname = "epson_qx10",
	.name = "Epson QX10",
	.attrs = {
		.cylinders = 40,
		.heads = 2,
		.sector_count = 10,
		.sector_size = 512,
		.block_size = 2048,
		.max_dir_entries = 128,
		.skew_table = epson_qx10_skew,
		.boot_cylinders = 4,
		.fill_order = CPM_FILL_NORMAL,
	},
	.encoding = ISOIBM_MFM_ENCODING,
};

static uint32_t sanco_8003_skew[5] = {1, 4, 2, 5, 3};
struct disk_definition sanco_8003 = {
	.shortname = "sanco_8003",
	.name = "Sanco 8003",
	.attrs = {
		.cylinders = 80,
		.heads = 2,
		.sector_count = 5,
		.sector_size = 1024,
		.block_size = 4096,
		.max_dir_entries = 128,
		.skew_table = sanco_8003_skew,
		.boot_cylinders = 2,
		.fill_order = CPM_FILL_NORMAL,
	},
	.encoding = ISOIBM_MFM_ENCODING,
};


static struct disk_definition *defs[] = {
	&bondwell_12,
	&epson_qx10,
	&micral_p2,
	&osborne_1,
	&otrona_attache,
	&sanco_8003,
};

struct disk_definition *find_definition(const char *name)
{
	for (size_t i = 0; i < sizeof(defs) / sizeof(struct disk_definition*); ++i)
		if (strcmp(name, defs[i]->shortname) == 0)
			return defs[i];
	fprintf(stderr, "Cannot find disk definition for \"%s\".\n", name);
	return NULL;
}

int print_formats(void)
{
	printf("Available formats:\n");
	for (size_t i = 0; i < sizeof(defs) / sizeof(struct disk_definition*); ++i)
		printf("%s: %s\n", defs[i]->shortname, defs[i]->name);
	return 0;
}