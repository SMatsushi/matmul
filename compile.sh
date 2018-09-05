#!/bin/sh

source /opt/nec/ve/mpi/1.1.0/bin/necmpivars.sh

ncc -DSXVE mat.c -lm -o amat
