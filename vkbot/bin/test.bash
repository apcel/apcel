#!/bin/bash
cmd='./main'
grid='55330593'
for ((i=0; i<=4472; i+=1000)); do
    # $cmd $grid $i
    ids=$i;
    for((j=i+1; j<i+1000; j+=1)); do
        ids=${ids}','$j
    done
    # echo $ids
    $cmd
done