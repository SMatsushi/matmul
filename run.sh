#!/bin/sh

source /opt/nec/ve/mpi/1.1.0/bin/necmpivars.sh

./amat
# ve_exec -N 1 amat
ftrace -f ftrace.out
