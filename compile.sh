#!/bin/sh

source /opt/nec/ve/mpi/1.1.0/bin/necmpivars.sh
cmd="ncc -ftrace -DSXVE mat.c -lm -o amat"
echo $cmd
$cmd
