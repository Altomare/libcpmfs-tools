/* Copyright (c) 2026 Arthur DAUZAT
 * SPDX-License-Identifier: BSD-3-Clause */

#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <libcpmfs.h>

#include "commands.h"
#include "floppy.h"

static int dump_unused_sectors(struct disk_definition *def)
{
	struct cpm_fs_dir *dirp;
	struct cpm_fs *fs;
	int status = CPM_SUCCESS;
	struct cpm_fs_crawler *crawler;
	uint8_t *block;

	status =
		cpm_fs_new(&def->attrs, &read_sector, &write_sector, NULL, &fs);
	if (status)
		goto end;

	status = cpm_fs_opendir(fs, &dirp);
	if (status != CPM_SUCCESS)
		goto end;

	status = cpm_fs_init_crawler(fs, &crawler);
	if (status != CPM_SUCCESS)
		goto end;

	status = cpm_fs_get_unused_blocks(fs, crawler, &block);
	while (status == CPM_SUCCESS && block != NULL) {
		for (uint32_t i = 0; i < def->attrs.block_size; ++i) {
			if (block[i] != 0xE5) {
				write(1, block, def->attrs.block_size);
				break;
			}
		}
		status = cpm_fs_get_unused_blocks(fs, crawler, &block);
	}

	cpm_fs_destroy_crawler(fs, crawler);
	cpm_fs_destroy(fs);

end:
	if (status != CPM_SUCCESS)
		fprintf(stderr, "CP/M error: %s\n", cpm_fs_status_str(status));
	return 0;
}

static void print_usage_exit(const char *name)
{
	printf("Output data from any unused sector that isn't wiped.\n"
	       "This is intended to be used alongside a binary viewer.\n"
	       "\n"
	       "Usage: %s <options>\n"
	       "\n"
	       "Options:\n"
	       "    -f,--format <format>   Target CP/M format (mandatory)\n"
	       "    -i,--input <path>      Input image file (mandatory)\n"
	       "    -h,--help              Displays this message\n"
	       "\n"
	       "Examples:\n"
	       "    recover -f micral_p2 -i image.md | xxd\n"
	       "    recover -f micral_p2 -i image.md > unused_sectors.bin\n",
	       name);
	exit(EXIT_FAILURE);
}

int recover(int argc, char *argv[])
{
	const char opts[] = "f:i:h";
	const struct option long_opts[] = {
		{"format", required_argument, 0, 'f'},
		{"input", required_argument, 0, 'i'},
		{"help", no_argument, 0, 'h'},
		{0, 0, 0, 0}};
	char path[1024 + 1] = {0};
	char format[128] = {0};
	struct disk_definition *def;
	int opt;

	while ((opt = getopt_long(argc, argv, opts, long_opts, NULL)) != -1) {
		switch (opt) {
		case 'i':
			strncpy(path, optarg, 1024);
			break;
		case 'f':
			strncpy(format, optarg, 128);
			break;
		case 'h':
		default:
			print_usage_exit(argv[0]);
			break;
		}
	}

	if (!path[0]) {
		fprintf(stderr, "Missing input file\n");
		exit(EXIT_FAILURE);
	}

	if (!format[0]) {
		fprintf(stderr, "Missing format\n");
		exit(EXIT_FAILURE);
	}
	if (optind > argc)
		print_usage_exit(argv[0]);

	def = find_definition(format);
	if (!def)
		return -1;

	if (init_floppy(path, def) != 0) {
		fprintf(stderr, "Unable to load disk image \"%s\"\n", path);
		return -1;
	}

	dump_unused_sectors(def);

	destroy_floppy();

	return 0;
}
