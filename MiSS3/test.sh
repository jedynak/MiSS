#!/bin/bash

for i in 1 2 3 4 5 6 7 8 9 10
do
    ./lab2 20 < out/$1$i.out > test_out/$1$i.out
done