#!/bin/bash

START=0
STOP=8
ONEAHEAD=$START


for (( i=$START; i < $STOP; i++ ))
do
  ONEAHEAD=$(($ONEAHEAD+1))
  crab submit crabNoPy.py
  sed -i "s/i=${i}/i=${ONEAHEAD}/" crabNoPy.py
done
