#!/bin/bash

set -xe

export PATH="$HOME/miniconda/bin:$PATH"
source $HOME/miniconda/bin/activate

# 2020
cd 2020/Courses/Calibration && bash make-slides.sh && cd -
cd 2020/Courses/Sensitivity && bash make-slides.sh && cd -
cd 2020/Courses/Metamodel/slides_PCEs/Latex && bash make-slides.sh && cd -
cd 2020/Courses/Metamodel/slides_GP/Latex && bash make-slides.sh && cd -

# 2021
cd 2021/Courses/Calibration && bash make-slides.sh && cd -
cd 2021/Courses/Metamodel/Introduction && bash make-slides.sh && cd -
cd 2021/Courses/Metamodel/slides_PCEs/Latex && bash make-slides.sh && cd -
cd 2021/Courses/Metamodel/slides_GP/Latex && bash make-slides.sh && cd -
cd 2021/Courses/Sensitivity && bash make-slides.sh && cd -
cd 2021/Scripts/Instructions && bash make-slides.sh && cd -
cd 2021/Courses/LinearAlgebra && bash make-slides.sh && cd -

# 2021
cd 2022/Courses/Calibration && bash make-slides.sh && cd -
cd 2022/Courses/Metamodel/Introduction && bash make-slides.sh && cd -
cd 2022/Courses/Metamodel/slides_PCEs/Latex && bash make-slides.sh && cd -
cd 2022/Courses/Metamodel/slides_GP/Latex && bash make-slides.sh && cd -
cd 2022/Courses/Sensitivity && bash make-slides.sh && cd -
cd 2022/Scripts/Instructions && bash make-slides.sh && cd -
cd 2022/Courses/LinearAlgebra && bash make-slides.sh && cd -

