#!/bin/bash

## Arguments
#

filedir="../process"
muanafile="run_00060.root"  # after  P5B <--> P6B switch
anadata=${filedir}/${muanafile}

if [ $# -ne 2 ] ; then
  echo ""
  echo "  !!! ./waveform_check.sh [Detector] [Event#] !!!"
  echo ""
  echo "     [1] CT, [2] Si, [3] EMT"
  echo ""
  echo ""
  exit 1
fi

detector=$1   # ex) [1] Si, [2] IC, [3] EMTC3, [4] EMTC4 
nevent=$2     # ex) 1000

## Execute analysis code
#
echo ""

cd ./bin
echo "  [["$anadata"]]"
echo ""
./waveform $anadata $detector $nevent


