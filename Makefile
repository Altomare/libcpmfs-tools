# Don't spam dir logs
MAKEFLAGS += --no-print-directory

CC := gcc
CXX := g++
CXXFLAGS := \
	-Wall -Wextra \
	-Igoogletest/googletest/include \
	-IHXC/include \
	-Ilibcpmfs/include
CFLAGS := \
	-Wall -Wextra -Wno-unused-parameter \
	-IHXC/include \
	-Ilibcpmfs/include

TOOLS_SRC := tools/main.c \
	     tools/disk_definitions.c \
	     tools/floppy.c \
	     tools/rm.c \
	     tools/ls.c \
	     tools/extract.c \
	     tools/wipe_unused_sectors.c
TOOLS_BIN := cpmfstools

TEST_SRC := \
	tests/test_libcpmfs.cpp \
	tests/disk_definitions.cpp \
	tests/floppy_utils.cpp
TEST_BIN := run_tests

# Deps
GTEST_BUILD := googletest/build
GTEST_LIBS  := $(GTEST_BUILD)/lib/libgtest.a

HXC_LIB := hxc/build/libhxcfe.so

LIBCPMFS_LIB := libcpmfs/build/libcpmfs.a

.PHONY: all clean hxc gtest libcpmfs test tools

all: $(TEST_BIN) $(TOOLS_BIN)

libcpmfs:
	@echo "Build libcpmfs"
	@$(MAKE) -C libcpmfs/ libcpmfs

hxc:
	@echo "Build libhxcfe"
	@$(MAKE) -C hxc/build/ libhxcfe

gtest:
	@echo "Build gtest"
	@mkdir -p $(GTEST_BUILD)
	@cd googletest/build && cmake .. && $(MAKE) gtest

test: $(TEST_BIN)
tools: $(TOOLS_BIN)

$(TEST_BIN): hxc gtest libcpmfs $(TEST_SRC)
	$(CXX) $(CXXFLAGS) \
	    -I hxc/libhxcfe/sources/ \
	    $(TEST_SRC) \
	    $(HXC_LIB) \
	    $(GTEST_LIBS) \
	    $(LIBCPMFS_LIB) \
	    -o $@
# 	    -pthread

$(TOOLS_BIN): libcpmfs $(TOOLS_SRC)
	$(CC) $(CFLAGS) \
	    -I hxc/libhxcfe/sources/ \
	    $(TOOLS_SRC) \
	    $(HXC_LIB) \
	    $(LIBCPMFS_LIB) \
	    -o $@


clean:
	rm -f $(TEST_BIN)
	$(MAKE) -C hxc/build/ clean
	$(MAKE) -C libcpmfs/ clean
	rm -rf googletest/build
