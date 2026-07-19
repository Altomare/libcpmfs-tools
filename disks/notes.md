# Notes about test disks

See https://www.idealine.info/sharpmz/dpb.htm


## Otrona Attaché

DPB, from BIOS sources. No sector translation table in DPH
```
SPT=40  BSH=4  BLM=15  EXM=1  DSM=181  DRM=127  AL0=0x80  AL1=0  CKS=32  OFF=3
```
With 96 TPI drives, EXM=0 and DSM=386

2 sides, 40 tracks per side, 10 sectors of 512 bytes per track.
Block size = 2048, max dir = 128
3 reserved tracks on side 0 for CP/M

In the physical sector headers, the order per track has a skew factor of 2:
1 6 2 7 3 8 4 9 5 10

But in the BIOS, there is no mention of that skew factor. It is only applied by
the FORMAT command when sending direct formatting commands to the disk. When the
BIOS requests a sector, it asks for the number to the µPD765 disk controller and
it locates it via the header. But since this is solely done by a format command
and the disk controller, the sectors could be ordered randomly and it would
still work.

Contrary to other disks, the block order is in HCS instead of CHS.
This means the first side will be entirely filled before starting to put files
on the second one.


## Zorba

* Side ID is not set in headers (always zero)
* Sectors are numbered 1 to 10 on side 0, and 11 to 20 on side 1
* 2 reserved tracks

```
CYLINDERS 40
SIDES 2
SECTORS 10,512
SKEW 2
SIDE1 0 1,2,3,4,5,6,7,8,9,10
SIDE2 0 11,12,13,14,15,16,17,18,19,20
ORDER SIDES
BSH 4 BLM 15 EXM 1 DSM 194 DRM 63 AL0 080H AL1 0 OFS 2
```

## Sanco

First track of side 0, 16 sector of 256 bytes. Rest is 5 * 1024.
No skew in sector headers, software skew (factor 2) applied by CP/M

diskdef sanco
  seclen 1024
  tracks 160
  sectrk 5
  blocksize 4096
  maxdir 128
  skew 2
  boottrk 2
  boottrkgeometry 256,16
  os 2.2
end

