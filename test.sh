#!/usr/bin/env bash
file="matrix-multiplication"

mpicc src/${file}.c -o out/${file}

for i in `seq 1 1`;
do
  echo "Test #${i}"

  output=$(mpirun -np 64 -hostfile ~/hostfile out/${file} < tests/${i}.in)
  diff ${output} tests/${i}.out

  if [ $? -eq 0 ]; then
    echo "Passed"
  fi
done
