/* Copyright (c) 2025 Arthur DAUZAT
 * SPDX-License-Identifier: BSD-3-Clause */

#include "floppy_utils.hh"

#include <stdexcept>

HxCFloppyImage::HxCFloppyImage(DiskSettings &settings) : settings_(settings) {

  int32_t ret;
  int loader_id;

  hxcfe_ = hxcfe_init();
  if (!hxcfe_)
    throw std::runtime_error("hxcfe_init");

  loader_ = hxcfe_imgInitLoader(hxcfe_);
  if (!loader_)
    throw std::runtime_error("hxcfe_imgInitLoader");

  loader_id = hxcfe_imgAutoSetectLoader(loader_,
                                        (char *)settings_.filename_.c_str(), 0);
  floppy_ref_ = hxcfe_imgLoad(loader_, (char *)settings_.filename_.c_str(),
                              loader_id, &ret);
  if (!floppy_ref_ || ret != 0)
    throw std::runtime_error("hxcfe_imgLoad");

  sector_access_ = NULL;
}

static int get_index_for_id(HXCFE* hxcfe, HXCFE_SECTORACCESS* sector_access, uint32_t cylinder, uint32_t head, int32_t sector, int type)
{
  HXCFE_SECTCFG * sc;
  int i = 0;

  hxcfe_resetSearchTrackPosition(sector_access);
  do
  {
    sc = hxcfe_getNextSector(sector_access,cylinder,head,type);
    if( sc )
    {
      if( i == sector ) {
        i = hxcfe_getSectorConfigSectorID(hxcfe, sc);
        hxcfe_freeSectorConfig(sector_access,sc);
        return i;
      }

      hxcfe_freeSectorConfig(sector_access,sc);
      i++;
}  }while( sc );
  return 0;
}

int HxCFloppyImage::read_sector(uint32_t cylinder, uint32_t head,
                                uint32_t sector, uint8_t *out_sector) const {
  int status;

  sector = get_index_for_id(hxcfe_, sector_access_, cylinder, head, sector, settings_.encoding_);
  hxcfe_readSectorData(sector_access_, cylinder, head, sector, 1,
                       settings_.attrs_.sector_size, settings_.encoding_,
                       out_sector, &status);

  if (status == FDC_NOERROR)
    return 0;
  return -1;
}

int HxCFloppyImage::write_sector(uint32_t cylinder, uint32_t head,
                                 uint32_t sector, const uint8_t *in_sector) {
  int status;

  sector = get_index_for_id(hxcfe_, sector_access_, cylinder, head, sector, settings_.encoding_);
  hxcfe_writeSectorData(sector_access_, cylinder, head, sector, 1,
                        settings_.attrs_.sector_size, settings_.encoding_,
                        (uint8_t *)in_sector, &status);

  if (status == FDC_NOERROR)
    return 0;
  return -1;
}

void HxCFloppyImage::reset_disk(void) {
  floppy_ = hxcfe_floppyDuplicate(hxcfe_, floppy_ref_);
  if (!floppy_)
    throw std::runtime_error("hxcfe_floppyDuplicate");

  if (sector_access_)
    hxcfe_deinitSectorAccess(sector_access_);
  sector_access_ = hxcfe_initSectorAccess(hxcfe_, floppy_);
  if (!sector_access_)
    throw std::runtime_error("hxcfe_initSectorAccess");
  // Some disks like Zorba ignore side ID
  hxcfe_setSectorAccessFlags(sector_access_, SECTORACCESS_IGNORE_SIDE_ID);
}

HxCFloppyImage::~HxCFloppyImage() {
  hxcfe_deinitSectorAccess(sector_access_);
  hxcfe_imgUnload(loader_, floppy_);
  hxcfe_imgUnload(loader_, floppy_ref_);
  hxcfe_imgDeInitLoader(loader_);
  hxcfe_deinit(hxcfe_);
}

extern "C" int cpm_get_sector(void *userdata, uint32_t cylinder, uint32_t head,
                              uint32_t sector, uint8_t *out_sector) {
  auto *image = static_cast<HxCFloppyImage *>(userdata);
  if (!image)
    return -1;
  return image->read_sector(cylinder, head, sector, out_sector);
}

extern "C" int cpm_set_sector(void *userdata, uint32_t cylinder, uint32_t head,
                              uint32_t sector, uint8_t *in_sector) {
  auto *image = static_cast<HxCFloppyImage *>(userdata);
  if (!image)
    return -1;
  return image->write_sector(cylinder, head, sector, in_sector);
}
