/* Copyright (c) 2026 Arthur DAUZAT
 * SPDX-License-Identifier: BSD-3-Clause */

#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include <libhxcfe.h>

#include "disk_definitions.h"

static struct disk_definition micral_p2 = {
	.shortname = "micral_p2",
	.name = "Bull Micral P2",
	.attrs = {
		.cylinders = 76,
		.heads = 2,
		.sector_count = 16,
		.sector_size = 256,
		.block_size = 2048,
		.max_dir_entries = 256,
		.skew_table = NULL,
		.skew_factor = 2,
		.boot_cylinders = 3,
		.fill_order = CPM_FILL_NORMAL,
	},
	.encoding = ISOIBM_MFM_ENCODING,
};

static struct disk_definition otrona_attache = {
	.shortname = "otrona_attache",
	.name = "Otrona Attache",
	.attrs = {
		.cylinders = 40,
		.heads = 2,
		.sector_count = 10,
		.sector_size = 512,
		.block_size = 2048,
		.max_dir_entries = 128,
		.skew_table = NULL,
		.skew_factor = 2,
		.boot_cylinders = 3,
		.fill_order = CPM_FILL_HCS,
	},
	.encoding = ISOIBM_MFM_ENCODING,
};

static struct disk_definition bondwell_12 = {
	.shortname = "bondwell_12",
	.name = "Bondwell 12",
	.attrs = {
		.cylinders = 40,
		.heads = 1,
		.sector_count = 18,
		.sector_size = 256,
		.block_size = 2048,
		.max_dir_entries = 64,
		.skew_table = NULL,
		.skew_factor = 2,
		.boot_cylinders = 2,
		.fill_order = CPM_FILL_NORMAL,
	},
	.encoding = ISOIBM_MFM_ENCODING,
};

static struct disk_definition osborne_1 = {
	.shortname = "osborne_1",
	.name = "Osborne 1",
	.attrs = {
		.cylinders = 40,
		.heads = 1,
		.sector_count = 10,
		.sector_size = 256,
		.block_size = 2048,
		.max_dir_entries = 64,
		.skew_table = NULL,
		.skew_factor = 2,
		.boot_cylinders = 3,
		.fill_order = CPM_FILL_NORMAL,
	},
	.encoding = ISOIBM_FM_ENCODING,
};

static uint32_t epson_qx10_skew[10] = {1, 8, 5, 2, 9, 6, 3, 10, 7, 4};
static struct disk_definition epson_qx10 = {
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
		.skew_factor = 0,
		.boot_cylinders = 4,
		.fill_order = CPM_FILL_NORMAL,
	},
	.encoding = ISOIBM_MFM_ENCODING,
};

static struct disk_definition sanco_8003 = {
	.shortname = "sanco_8003",
	.name = "Sanco 8003",
	.attrs = {
		.cylinders = 80,
		.heads = 2,
		.sector_count = 5,
		.sector_size = 1024,
		.block_size = 4096,
		.max_dir_entries = 128,
		.skew_table = NULL,
		.skew_factor = 2,
		.boot_cylinders = 2,
		.fill_order = CPM_FILL_NORMAL,
	},
	.encoding = ISOIBM_MFM_ENCODING,
};

static struct disk_definition osborne_4 = {
	.shortname = "osborne_4",
	.name = "Osborne Vixen",
	.attrs = {
		.cylinders = 40,
		.heads = 2,
		.sector_count = 5,
		.sector_size = 1024,
		.block_size = 2048,
		.max_dir_entries = 128,
		.skew_table = NULL,
		.skew_factor = 2,
		.boot_cylinders = 2,
		.fill_order = CPM_FILL_NORMAL,
	},
	.encoding = ISOIBM_MFM_ENCODING,
};

static struct disk_definition mai_basic4 = {
	.shortname = "mai_basic4",
	.name = "MAI Basic 4",
	.attrs = {
		.cylinders = 80,
		.heads = 2,
		.sector_count = 16,
		.sector_size = 256,
		.block_size = 2048,
		.max_dir_entries = 128,
		.skew_table = NULL,
		.skew_factor = 0,
		.boot_cylinders = 3,
		.fill_order = CPM_FILL_NORMAL,
	},
	.encoding = ISOIBM_MFM_ENCODING,
};

static struct disk_definition zorba = {
	.shortname = "zorba",
	.name = "Zorba",
	.attrs = {
		.cylinders = 40,
		.heads = 2,
		.sector_count = 10,
		.sector_size = 512,
		.block_size = 2048,
		.max_dir_entries = 64,
		.skew_table = NULL,
		.skew_factor = 0,
		.boot_cylinders = 2,
		.fill_order = CPM_FILL_NORMAL,
	},
	.encoding = ISOIBM_MFM_ENCODING,
};

static struct disk_definition ns_advantage = {
	.shortname = "ns_advantage",
	.name = "Northstar Advantage",
	.attrs = {
		.cylinders = 35,
		.heads = 1,
		.sector_count = 10,
		.sector_size = 512,
		.block_size = 2048,
		.max_dir_entries = 64,
		.skew_table = NULL,
		.skew_factor = 0,
		.boot_cylinders = 2,
		.fill_order = CPM_FILL_NORMAL,
	},
	.encoding = NORTHSTAR_HS_MFM_ENCODING,
};

static struct disk_definition *defs[] = {
	&bondwell_12,
	&epson_qx10,
	&micral_p2,
	&osborne_1,
	&otrona_attache,
	&sanco_8003,
	&osborne_4,
	&mai_basic4,
	&zorba,
	&ns_advantage,
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