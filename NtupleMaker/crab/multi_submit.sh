#!/bin/bash

START=0
STOP=9
ONEAHEAD=$START


for (( i=$START; i < $STOP; i++ ))
do
  ONEAHEAD=$(($ONEAHEAD+1))
  sed -i "s/i=${i}/i=${ONEAHEAD}/" crabNoPy.py
  crab submit crabNoPy.py
done
