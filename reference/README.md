# References

CPMDISKS.144 contains disk definitions from 22DISK version 1.44. newdisks is from gaby.de.

diskdefs is from cpmtools 2.23.

## cpmtools

cpmtools disk definitions sometimes contain  a `side` parameter about how the
disk is filled, but it doesn't seem to be used in 2.23.

Values can be:
* `alt`: fill in HCS order (fill side first instead of cylinder first)
* `outback`: fill in HCS order, side 1 is written from the outermost cylinder
* `outout`: fill in HCS order, starting from outermost cylinder

# 22DISK

## ORDER

22DISK has an `ORDER` parameter:
* `SIDES`: specifies that first one side then the other is written/read
      before the cylinder number is advanced.
* `CYLINDERS`: specifies that all tracks on the first side are recorded
      then all tracks on second side.  Tracks on side 0 are written
      from 0 up and side 1 down to 0.
* `EAGLE`: same as CYLINDERS except both sides start at zero or outermost
      track.
* `COLUMBIA`: same as CYLINDERS except tracks are sequential from side
      0 to side 1 ie. 0 - 79 for a 40 track disk.
* `EVEN-ODD` means side 0 contains even-numbered tracks and side 1
      contains odd-numbered tracks. 
* `SKIP`: means skip the first Single Density Track
