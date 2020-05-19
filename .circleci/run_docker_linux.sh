#!/bin/bash

set -xe

cd 2020/Scripts/Calibration && bash run-all.sh && cd -
cd 2020/Courses/Calibration && bash make-slides.sh && cd -
cd 2020/Courses/Sensitivity && bash make-slides.sh && cd -
cd 2020/Courses/Metamodel/slides_PCEs/Latex && bash make-slides.sh && cd -
cd 2020/Courses/Metamodel/slides_GP/Latex && bash make-slides.sh && cd -

