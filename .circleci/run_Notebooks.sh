#!/bin/bash

set -xe

# Notebooks in all subdirectories
cd 2020
python ../tests/find-ipynb-files.py
cd ..

