#!/bin/sh

source /opt/nec/ve/mpi/1.1.0/bin/necmpivars.sh

# ./amat
for cmd in \
    "ve_exec -N 0 afmat"\
    "ve_exec -N 1 afmat"\
    "ve_exec -N 2 afmat"\
    "ve_exec -N 3 afmat"
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

