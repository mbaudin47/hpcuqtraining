#!/bin/sh

test_python_script()
{
  # test_python_script mypythonscript.py
  pythonscript=$1
  cp $pythonscript /tmp
  python /tmp/$pythonscript
}

test_ipython_notebook()
{
  # test_ipython_notebook mynotebook.ipynb
  ipythonnotebook=$1
  basefilename=$(basename -- "$ipythonnotebook")
  basefilename="${basefilename%.*}"
  nbfile="$basefilename.ipynb"
  pyfile="$basefilename.py"
  jupyter nbconvert --to python $nbfile
  mv $pyfile /tmp
  python /tmp/$pyfile
}

test_ipython_directory()
{
  FILES=*.ipynb
  for f in $FILES
  do
    echo "Processing $f file..."
    test_ipython_notebook $f
  done
}

set -xe

echo "Python interpreter"
echo `which python`
echo "OpenTURNS version"
python -c "import openturns; print(openturns.__version__); exit()"

# Run tests
test_ipython_directory

