#!/bin/bash
grep "cms.Schedule" >> schedule.txt;
sed 's/,/\n/g' schedule.txt;
