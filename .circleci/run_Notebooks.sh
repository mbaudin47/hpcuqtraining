#!/bin/bash

set -xe

export PATH="$HOME/miniconda/bin:$PATH"
source $HOME/miniconda/bin/activate

# Notebooks in all subdirectories
cd 2021
python ../tests/find-ipynb-files.py
cd ..

