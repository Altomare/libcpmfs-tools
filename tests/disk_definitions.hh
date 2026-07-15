#pragma once

#include <string>

#include <libcpmfs.h>
#include <libhxcfe.h>

class DiskSettings {
public:
  DiskSettings(const std::string &name, struct cpm_fs_attr attrs,
               std::string filename, int encoding)
      : name_(name), attrs_(attrs), filename_(filename), encoding_(encoding) {}

  std::string name_;
  struct cpm_fs_attr attrs_;
  std::string filename_;
  int encoding_;
};

extern DiskSettings OtronaAttache;
extern DiskSettings Bondwell12;
extern DiskSettings Osborne1;
extern DiskSettings EpsonQX10;
extern DiskSettings Sanco8003;
extern DiskSettings OsborneVixen;
extern DiskSettings Zorba;
extern DiskSettings MaiBasicFour;
