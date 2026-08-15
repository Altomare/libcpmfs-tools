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

static int wipe_sectors(struct disk_definition *def)
{
	struct cpm_fs_dir *dirp;
	struct cpm_fs *fs;
	int status;

	status =
		cpm_fs_new(&def->attrs, &read_sector, &write_sector, NULL, &fs);
	if (status)
		goto end;

	status = cpm_fs_opendir(fs, &dirp);
	if (status != CPM_SUCCESS)
		goto end;

	status = cpm_fs_wipe_unused_sectors(fs);
	if (status != CPM_SUCCESS)
		goto end;

	status = cpm_fs_sync(fs);
	cpm_fs_destroy(fs);

end:
	if (status != CPM_SUCCESS)
		fprintf(stderr, "CP/M error: %s\n", cpm_fs_status_str(status));
	return 0;
}

static void print_usage_exit(void)
{
	// TODO
	exit(EXIT_FAILURE);
}

int wipe_unused_sectors(int argc, char *argv[])
{
	const char opts[] = "f:";
	const struct option long_opts[] = {
		{"format", required_argument, 0, 'f'}, {0, 0, 0, 0}};
	char path[1024] = {0};
	char format[128] = {0};
	struct disk_definition *def;
	int opt;

	while ((opt = getopt_long(argc, argv, opts, long_opts, NULL)) != -1) {
		switch (opt) {
		case 'f':
			printf("Format = %s\n", optarg);
			memcpy(format, optarg, strlen(optarg));
			break;
		default:
			print_usage_exit();
			break;
		}
	}

	if (optind != argc - 1)
		print_usage_exit();

	memcpy(path, argv[optind], strlen(argv[optind]));

	if (!path[0] || !format[0])
		print_usage_exit();

	def = find_definition(format);
	if (!def)
		return -1;

	if (init_floppy(path, def) != 0) {
		fprintf(stderr, "Fail\n");
		return -1;
	}
	wipe_sectors(def);

	save_floppy("toto.imd");
	destroy_floppy();

	return 0;
}
