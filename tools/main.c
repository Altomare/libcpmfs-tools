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
	{
		.name = "rm",
		.func = &rm,
	},
	{
		.name = "cleanup",
		.func = &cleanup,
	},
};

static void usage(const char *name)
{
	fprintf(stderr,
		"Set of tools to manipulate CP/M floppy disk image files.\n"
		"\n"
		"Usage: %s <command> <arguments>\n"
		"\n"
		"Available commands:\n"
		"    ls                   List files\n"
		"    extract              Extract all files\n"
		"    rm                   Delete specified files\n"
		"    cleanup              Cleanup unused sectors\n"
		"    list_formats         List available disk formats\n"
		"\n"
		"For more details on a command, run:\n"
		"    %s <command> --help\n"
		, name, name);
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
