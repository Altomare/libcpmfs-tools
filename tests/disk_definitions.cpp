
#include <string>

#include "disk_definitions.hh"

/* Otrona Attaché, CP/M 2.2, default configuration with 48 TPI drives.
 * First 3 tracks of side 0 are reserved for CP/M.
 * Disk is filled head by head instead of track by track. */
static uint32_t otrona_attache_skew[10] = {1, 6, 2, 7, 3, 8, 4, 9, 5, 10};
DiskSettings OtronaAttache(
  "Otrona_Attache",
  {
    .cylinders = 40,
    .heads = 2,
    .sector_count = 10,
    .sector_size = 512,
    .block_size = 2048,
    .max_dir_entries = 128,
    .skew_table = otrona_attache_skew,
    .boot_cylinders = 3,
    .fill_order = CPM_FILL_HCS,
  },
  "disks/otrona.td0",
  ISOIBM_MFM_ENCODING);

/* Bondwell 12 - CP/M 2.2
 * 2 tracks reserved for CP/M. */
static uint32_t bondwell_12_skew[18] = {1, 10, 2, 11, 3, 12, 4, 13, 5, 14, 6, 15, 7, 16, 8, 17, 9, 18};
DiskSettings Bondwell12(
  "Bondwell_12",
  {
    .cylinders = 40,
    .heads = 1,
    .sector_count = 18,
    .sector_size = 256,
    .block_size = 2048,
    .max_dir_entries = 64,
    .skew_table = bondwell_12_skew,
    .boot_cylinders = 2,
    .fill_order = CPM_FILL_NORMAL,
  },
  "disks/bondwl12.td0",
  ISOIBM_MFM_ENCODING);

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
    .fill_order = CPM_FILL_NORMAL,
  },
  "disks/osborne_1_bootable.td0",
  ISOIBM_FM_ENCODING);

static uint32_t epson_qx10_skew[10] = {1, 8, 5, 2, 9, 6, 3, 10, 7, 4};
DiskSettings EpsonQX10(
  "Epson_QX10",
  {
    .cylinders = 40,
    .heads = 2,
    .sector_count = 10,
    .sector_size = 512,
    .block_size = 2048,
    .max_dir_entries = 128,
    .skew_table = epson_qx10_skew,
    .boot_cylinders = 4,
    .fill_order = CPM_FILL_NORMAL,
  },
  "disks/epson_qx10_cpm2.2.td0",
  ISOIBM_MFM_ENCODING);

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
    .fill_order = CPM_FILL_NORMAL,
  },
  "disks/SANCO8003_CPM_2.2fr.dsqd.hfe",
  ISOIBM_MFM_ENCODING);

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
    .fill_order = CPM_FILL_NORMAL,
  },
  "disks/osborne_vixen_bootable.td0",
  ISOIBM_MFM_ENCODING);

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
    .fill_order = CPM_FILL_NORMAL,
  },
  "disks/MAI4CPM.IMD",
  ISOIBM_MFM_ENCODING);

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
    .fill_order = CPM_FILL_NORMAL,
  },
  "disks/ZORBA1.IMD",
  ISOIBM_MFM_ENCODING);


DiskSettings NorthstarAdvantage(
  "Northstar_Advantage",
  {
    .cylinders = 35,
    .heads = 1,
    .sector_count = 10,
    .sector_size = 512,
    .block_size = 2048,
    .max_dir_entries = 64,
    .skew_table = NULL,
    .boot_cylinders = 2,
    .fill_order = CPM_FILL_NORMAL,
  },
  "disks/northstar_advantage_cpm_basic.nsi",
  NORTHSTAR_HS_MFM_ENCODING);
