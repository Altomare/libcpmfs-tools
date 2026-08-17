/* Copyright (c) 2026 Arthur DAUZAT
 * SPDX-License-Identifier: BSD-3-Clause */

#pragma once

#include <libcpmfs.h>

struct disk_definition {
	char *shortname;
	char *name;
	struct cpm_fs_attr attrs;
	int encoding;
};

struct disk_definition *find_definition(const char *name);
int print_formats(void);
