#!/bin/sh

source /opt/nec/ve/mpi/1.1.0/bin/necmpivars.sh

# ./amat
for cmd in \
    "ve_exec -N 1 afmat"\
    "./apfmat 8"\
    "./alpfmat 8"\
    "env VE_PROGINF=YES ./alptmat 8"\
    "./alpmat 8"
    do
        rm -f ./ftrace.out
        echo $cmd
        time $cmd
        echo
        if [ -f ./ftrace.out ]; then
              ftrace -f ./ftrace.out
        fi
        echo '----------------------'
done  

