#!/bin/bash
# chmod u+x makeplots.sh
# source makeplots.sh
  
make clean
source setup.sh
make
./MadAnalysis5job input.txt
