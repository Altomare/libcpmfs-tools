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

static int cpmrm(struct disk_definition *def, const char *filename, int user)
{
	struct cpm_fs *fs;
	int status;

	status =
		cpm_fs_new(&def->attrs, &read_sector, &write_sector, NULL, &fs);
	if (status)
		goto end;

	status = cpm_fs_unlink(fs, filename, user);
	if (status)
		goto end;

	cpm_fs_sync(fs);

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

int rm(int argc, char *argv[])
{
	const char opts[] = "f:u:i:o:";
	const struct option long_opts[] = {
		{"format", required_argument, 0, 'f'},
		{"user", required_argument, 0, 'u'},
		{"image", required_argument, 0, 'i'},
		{"output", required_argument, 0, 'o'},
		{0, 0, 0, 0}};
	char path[1024 + 1] = {0};
	char output[1024 + 1] = {0};
	char format[128] = {0};
	struct disk_definition *def;
	int user = 0;
	int opt;

	while ((opt = getopt_long(argc, argv, opts, long_opts, NULL)) != -1) {
		switch (opt) {
		case 'i':
			printf("File = %s\n", optarg);
			strncpy(path, optarg, 1024);
			break;
		case 'o':
			printf("File = %s\n", optarg);
			strncpy(output, optarg, 1024);
			break;
		case 'f':
			printf("Format = %s\n", optarg);
			strncpy(format, optarg, 1024);
			break;
		case 'u':
			user = strtol(optarg, NULL, 10);
			printf("User = %d\n", user);
			break;
		default:
			print_usage_exit();
			break;
		}
	}

	if (!path[0] || !format[0] || optind >= argc)
		print_usage_exit();

	if (!output[0])
		memcpy(output, path, 1024);

	def = find_definition(format);
	if (!def)
		return -1;

	if (init_floppy(path, def) != 0) {
		fprintf(stderr, "Fail\n");
		return -1;
	}

	for (; optind < argc; ++optind)
		cpmrm(def, argv[optind], user);

	save_floppy(output);
	destroy_floppy();

	return 0;
}
