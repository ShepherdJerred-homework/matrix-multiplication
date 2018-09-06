#!/usr/bin/env bash
fileName="matrix-multiplication"

mpicc src/${fileName}.c -o out/${fileName}

mpirun -np 4 -hostfile ~/hostfile out/${fileName}
