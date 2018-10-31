# Makefile for
#   Blocked dense matrix multiplication
#  (C) 2018 NEC Enterprise Communication Tech. Inc
#
# This software is provided "as is" without warranty of any kind.
#

CFLAGS = -O3 -lm
BIGFLAGS = -DSXVE
all: mat lmat
mat: mat.o
	$(CC) $(CFLAGS) -o $@ $<
lmat: mat.c
	$(CC) $(CFLAGS) $(BIGFLAGS) -o $@ $< 
clean:
	/bin/rm -f mat lmat amat apmat alpmat afmat apfmat alpfmat alptmat alpmat ftrace.out mat.o 
