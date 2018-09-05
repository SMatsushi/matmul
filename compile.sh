#!/bin/sh

source /opt/nec/ve/mpi/1.1.0/bin/necmpivars.sh

baseflag="-O3 -ftrace -DSXVE -lm"
pflag=" ${baseflag} -mparallel"

cmd="ncc ${baseflag} mat.c -o amat"
echo $cmd
$cmd

cmd="ncc ${pflag} mat.c -o apmat"
echo $cmd
$cmd

cmd="ncc ${pflag} -DSXLG mat.c -o alpmat"
echo $cmd
$cmd
