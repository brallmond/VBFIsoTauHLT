#!/bin/bash

START=1
STOP=19
ONEAHEAD=$START


for (( i=$START; i < $STOP; i++ ))
do
  ONEAHEAD=$(($ONEAHEAD+1))
  crab submit crabNoPy.py
  sed -i "s/i=${i}/i=${ONEAHEAD}/" crabNoPy.py
done
