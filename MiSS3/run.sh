#!/bin/bash

for i in 1 2 3 4 5 6 7 8 9 10
do
    ./$1 1 65535 < in/$1$i.in > out/$1$i.out
done