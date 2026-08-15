/* Copyright (c) 2026 Arthur DAUZAT
 * SPDX-License-Identifier: BSD-3-Clause */

#pragma once

#include <stdint.h>

#include "disk_definitions.h"

int init_floppy(char *filename, const struct disk_definition *diskdef);
void destroy_floppy(void);
int save_floppy(char *filename);

int read_sector(void *userdata, uint32_t c, uint32_t h, uint32_t s, uint8_t *out_s);
int write_sector(void *userdata, uint32_t c, uint32_t h, uint32_t s, uint8_t *in_s);
