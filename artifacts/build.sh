#!/bin/sh

cd ../build
cmake ..
make
#rm -r ../artifacts/shaders
#cp -r ../src/experimentum/shaders ../artifacts
cd ../artifacts
