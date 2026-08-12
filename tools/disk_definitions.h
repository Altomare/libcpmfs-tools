#pragma once

#include <libcpmfs.h>

struct disk_definition {
	char *shortname;
	char *name;
	struct cpm_fs_attr attrs;
	int encoding;
};

extern struct disk_definition micral_p2;

struct disk_definition *find_definition(const char *name);
int print_formats(void);
