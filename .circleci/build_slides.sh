#!/bin/bash

set -xe

export PATH="$HOME/miniconda/bin:$PATH"
source $HOME/miniconda/bin/activate

cd 2021/Courses/Calibration && bash make-slides.sh && cd -
cd 2020/Courses/Sensitivity && bash make-slides.sh && cd -
cd 2021/Courses/Metamodel/slides_PCEs/Latex && bash make-slides.sh && cd -
cd 2021/Courses/Metamodel/slides_GP/Latex && bash make-slides.sh && cd -

