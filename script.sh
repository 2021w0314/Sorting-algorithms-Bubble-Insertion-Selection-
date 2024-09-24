#!/bin/bash
clear   
make clean && make
./sorting
python3 matplot.py

# ''' chmod +x ./***.sh '''
# ''' ./***.sh '''