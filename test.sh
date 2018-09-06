#!/usr/bin/env bash
file="matrix-multiplication"

mkdir -p out

mpicc src/${file}.c -o out/${file}

testProcessCount=(4, 4);

for i in `seq 1 2`;
do
  echo "Test #${i}"

  mpirun -np ${testProcessCount[${i} - 1]} -hostfile ~/hostfile out/${file} < tests/${i}.in > tests/${i}.actual.out

  diff -u tests/${i}.actual.out tests/${i}.out

  if [ $? -eq 0 ]; then
    echo "Passed"
  fi
done
