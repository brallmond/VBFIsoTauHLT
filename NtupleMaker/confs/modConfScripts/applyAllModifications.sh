#!/bin/bash
FILE=$1
. modConfScripts/addAODConf.sh $FILE
. modConfScripts/changeMaxEventsToAll.sh $FILE
. modConfScripts/removeDQMIO.sh $FILE
