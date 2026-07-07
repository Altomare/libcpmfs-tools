
#include <string>

#include "disk_definitions.hh"

/* Otrona Attaché, CP/M 2.2, default configuration with 48 TPI drives.
 * First 3 tracks of side 0 are reserved for CP/M. */
DiskSettings OtronaAttache(
  "Otrona_Attache",
  {
    .cylinders = 40,
    .heads = 2,
    .sector_count = 10,
    .sector_size = 512,
    .block_size = 2048,
    .max_dir_entries = 128,
    .skew_table = NULL,
    .boot_cylinders = 3,
    .hcs_fill = 1,
  },
  "disks/otrona.td0",
  ISOIBM_MFM_ENCODING,
  1);

/* Bondwell 12 - CP/M 2.2
 * 2 tracks reserved for CP/M. */
DiskSettings Bondwell12(
  "Bondwell_12",
  {
    .cylinders = 40,
    .heads = 1,
    .sector_count = 18,
    .sector_size = 256,
    .block_size = 2048,
    .max_dir_entries = 64,
    .skew_table = NULL,
    .boot_cylinders = 2,
    .hcs_fill = 0,
  },
  "disks/bondwl12.td0",
  ISOIBM_MFM_ENCODING,
  0);

static uint32_t osborne_1_skew[10] = {1, 6, 2, 7, 3, 8, 4, 9, 5, 10};
DiskSettings Osborne1(
  "Osborne_1",
  {
    .cylinders = 40,
    .heads = 1,
    .sector_count = 10,
    .sector_size = 256,
    .block_size = 2048,
    .max_dir_entries = 64,
    .skew_table = osborne_1_skew,
    .boot_cylinders = 3,
    .hcs_fill = 0,
  },
  "disks/osborne_1_bootable.td0",
  ISOIBM_FM_ENCODING,
  1);

DiskSettings EpsonQX10(
  "Epson_QX10",
  {
    .cylinders = 40,
    .heads = 2,
    .sector_count = 10,
    .sector_size = 512,
    .block_size = 2048,
    .max_dir_entries = 128,
    .skew_table = NULL,
    .boot_cylinders = 4,
    .hcs_fill = 0,
  },
  "disks/epson_qx10_cpm2.2.td0",
  ISOIBM_MFM_ENCODING,
  1);

static uint32_t sanco_8003_skew[5] = {1, 4, 2, 5, 3};
DiskSettings Sanco8003(
  "Sanco_8003",
  {
    .cylinders = 80,
    .heads = 2,
    .sector_count = 5,
    .sector_size = 1024,
    .block_size = 4096,
    .max_dir_entries = 128,
    .skew_table = sanco_8003_skew,
    .boot_cylinders = 2,
    .hcs_fill = 0,
  },
  "disks/SANCO8003_CPM_2.2fr.dsqd.hfe",
  ISOIBM_MFM_ENCODING,
  1);

static uint32_t osborne_vixen_skew[5] = {1, 4, 2, 5, 3};
DiskSettings OsborneVixen(
  "Osborne_Vixen",
  {
    .cylinders = 40,
    .heads = 2,
    .sector_count = 5,
    .sector_size = 1024,
    .block_size = 2048,
    .max_dir_entries = 128,
    .skew_table = osborne_vixen_skew,
    .boot_cylinders = 2,
    .hcs_fill = 0,
  },
  "disks/osborne_vixen_bootable.td0",
  ISOIBM_MFM_ENCODING,
  1);

DiskSettings MaiBasicFour(
  "MAI_Basic4",
  {
    .cylinders = 80,
    .heads = 2,
    .sector_count = 16,
    .sector_size = 256,
    .block_size = 2048,
    .max_dir_entries = 128,
    .skew_table = NULL,
    .boot_cylinders = 3,
    .hcs_fill = 0,
  },
  "disks/MAI4CPM.IMD",
  ISOIBM_MFM_ENCODING,
  1);

DiskSettings Zorba(
  "Zorba",
  {
    .cylinders = 40,
    .heads = 2,
    .sector_count = 10,
    .sector_size = 512,
    .block_size = 2048,
    .max_dir_entries = 64,
    .skew_table = NULL,
    .boot_cylinders = 2,
    .hcs_fill = 0,
  },
  "disks/ZORBA1.IMD",
  ISOIBM_MFM_ENCODING,
  1);
