#!/bin/bash

set -xe

export PATH="$HOME/miniconda/bin:$PATH"
source $HOME/miniconda/bin/activate
#
cd 2020/Scripts/Calibration && bash run-all.sh && cd -
cd 2020/Courses/Calibration && bash make-slides.sh && cd -

