# libcomfs-tools

Set of tests and tools based on [libcpmfs](https://github.com/Altomare/libcpmfs).

Both use `libhxcfe` to read disk image files, from
[HxCFloppyEmulator](https://github.com/jfdelnero/HxCFloppyEmulator).


## Tools

Available commands:
* ls: List files
* extract: Extract all files
* rm: Delete specified files
* cleanup: Cleanup unused sectors
* list_formats: List available disk formats

Disk image formats are hardcoded in tools/disk_definitions.c, but I plan on
adding a way to manually add formats, just like 22disk custom formats.


## Tests

Tests run a few libcpmfs commands on a subset of disk files, contained in disks/.

There are issues currently with Northstar disks, caused by sector access.


## Build

Only Linux is supported at the moment, although I plan on adding Windows and Mac
targets.

### Linux

```bash
git submodule update
make
```


## Licensing

Released under BSD 3-clause license. See `LICENSE`

`libhxcfe` is released under GNU GPL V3.
