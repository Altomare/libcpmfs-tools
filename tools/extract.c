/* Copyright (c) 2026 Arthur DAUZAT
 * SPDX-License-Identifier: BSD-3-Clause */

#include <fcntl.h>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include <libcpmfs.h>

#include "commands.h"
#include "floppy.h"

static void dump_file(struct cpm_fs *fs, struct cpm_fs_file *cpmfile)
{
	struct cpm_fs_file_handle *f;
	char new_name[256];
	uint8_t buf[513];
	size_t read_bytes;
	int new_f;
	enum cpm_fs_status status;

	memcpy(new_name, cpmfile->d_name, 16);
	for (int i = 0; i < 256; ++i) {
		if (new_name[i] == '/')
			new_name[i] = '_';
		if (new_name[i] == ':')
			new_name[i] = '.';
	}

	printf("%d:%s -> %s\n", cpmfile->d_user, cpmfile->d_name, new_name);

	if (access(new_name, F_OK) == 0) {
		fprintf(stderr, "\t%s already exists.\n", new_name);
		return;
	}

	new_f = open(new_name,
		     O_CREAT | O_RDWR,
		     S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (!new_f) {
		fprintf(stderr, "\tUnable to open %s.\n", new_name);
		return;
	}
	status = cpm_fs_open(
		fs, cpmfile->d_name, CPM_MODE_RDONLY, cpmfile->d_user, &f);
	if (!f) {
		fprintf(stderr, "\t[CPM] Unable to open %s\n", cpmfile->d_name);
		return;
	}

	status = cpm_fs_read(fs, f, buf, 512, &read_bytes);
	while (status == CPM_SUCCESS && read_bytes > 0) {
		write(new_f, buf, read_bytes);
		status = cpm_fs_read(fs, f, buf, 512, &read_bytes);
	}
	if (status != CPM_SUCCESS)
		fprintf(stderr, "Read error: %s\n", cpm_fs_status_str(status));

	cpm_fs_close(fs, f);
	close(new_f);
}

static int cpmextract(struct disk_definition *def)
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

	struct cpm_fs_file *cpmfile;
	cpm_fs_readdir(fs, dirp, &cpmfile);
	while (cpmfile) {
		if (cpmfile->d_size > 0)
			dump_file(fs, cpmfile);
		else
			printf("Skipped empty file %s\n", cpmfile->d_name);
		cpm_fs_readdir(fs, dirp, &cpmfile);
	}
	cpm_fs_closedir(fs, dirp);

	cpm_fs_destroy(fs);

end:
	if (status != CPM_SUCCESS)
		fprintf(stderr, "CP/M error: %s\n", cpm_fs_status_str(status));
	return 0;
}

static void print_usage_exit(const char *name)
{
	printf("Extract every file from given CP/M disk image.\n"
	       "\n"
	       "Usage: %s <options>\n"
	       "\n"
	       "Options:\n"
	       "    -f,--format <format>   Target CP/M format (mandatory)\n"
	       "    -i,--input <path>      Input image file (mandatory)\n"
	       "    -h,--help              Displays this message\n",
	       name);
	exit(EXIT_FAILURE);
}
int extract(int argc, char *argv[])
{
	const char opts[] = "f:i:h";
	const struct option long_opts[] = {
		{"format", required_argument, 0, 'f'},
		{"input", required_argument, 0, 'i'},
		{"help", no_argument, 0, 'h'},
		{0, 0, 0, 0}};
	char path[1024] = {0};
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

	def = find_definition(format);
	if (!def)
		return -1;

	if (init_floppy(path, def) != 0) {
		fprintf(stderr, "Fail\n");
		return -1;
	}
	cpmextract(&micral_p2);
	destroy_floppy();

	return 0;
}
