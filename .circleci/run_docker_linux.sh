#!/bin/bash

set -xe

export PATH="$HOME/miniconda/bin:$PATH"
source $HOME/miniconda/bin/activate

cd 2021/Scripts/Calibration && bash run-all.sh && cd -

