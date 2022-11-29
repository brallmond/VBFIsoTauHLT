#!/bin/bash

START=0
STOP=10
ONEAHEAD=$START


for (( i=$START; i < $STOP; i++ ))
do
  ONEAHEAD=$(($ONEAHEAD+1))
  sed -i "s/i=${i}/i=${ONEAHEAD}/" dummy.txt
  cat dummy.txt
done
