/* Copyright (c) 2026 Arthur DAUZAT
 * SPDX-License-Identifier: BSD-3-Clause */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "commands.h"
#include "disk_definitions.h"

struct command {
	char *name;
	int (*func)(int ac, char *av[]);
};

int list_formats(int argc, char *argv[])
{
	return print_formats();
}

static struct command cmds[] = {
	{
		.name = "ls",
		.func = &ls,
	},
	{
		.name = "extract",
		.func = &extract,
	},
	{
		.name = "list_formats",
		.func = &list_formats,
	},
};

static void usage(const char *name)
{
	fprintf(stderr, "Usage: %s <command> <arguments>\n", name);
	fprintf(stderr, "Commands: ls -t <format> <image>\n");
	fprintf(stderr, "          extract -t <format> <image>\n");
}

int main(int argc, char *argv[])
{
	if (argc < 2) {
		usage(argv[0]);
		exit(EXIT_FAILURE);
	}

	for (size_t i = 0; i < (sizeof(cmds) / sizeof(struct command)); ++i)
		if (strcmp(argv[1], cmds[i].name) == 0)
			return cmds[i].func(argc - 1, argv + 1);

	usage(argv[0]);
	return -1;
}
