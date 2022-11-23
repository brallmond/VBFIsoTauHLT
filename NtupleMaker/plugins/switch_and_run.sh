#!/bin/bash
cd ../confs/;
cmsRun hlt2022DataDummyL1EGOR.py > std_output.txt;
cat std_output.txt;
cd ../plugins/;
