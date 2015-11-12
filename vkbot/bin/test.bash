#!/bin/bash
cmd='./main'
grid='55330593'
for ((i=1; i<=4472; i+=1000)); do
    $cmd $grid $i
done