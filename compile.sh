#!/bin/sh

source /opt/nec/ve/mpi/1.1.0/bin/necmpivars.sh

baseflag="-O3 -DSXVE -lm"
parflag=" ${baseflag} -mparallel"
ftflag="${baseflag} -ftrace"
ptflag="${baseflag} -proginf"
parftflag="${parflag} -ftrace"
parptflag="${parflag} -proginf"

for cmd in \
    "ncc ${ftflag} mat.c -o afmat"\
    "ncc ${parftflag} mat.c -o apfmat"\
    "ncc ${parftflag} -DSXLG mat.c -o alpfmat"\
    "ncc ${parptflag}  -DSXLG mat.c -o alptmat"\
    "ncc ${parflag} -DSXLG mat.c -o alpmat"
    do  echo $cmd
        time $cmd
        echo '-------------'
done
