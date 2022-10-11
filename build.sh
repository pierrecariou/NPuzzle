#!/bin/bash
# File              : build.sh
# Author            : Pierre Cariou <pierrecariou@outlook.fr>
# Date              : 28.07.2022
# Last Modified Date: 28.07.2022
# Last Modified By  : Pierre Cariou <pierrecariou@outlook.fr>

rm -rf build
mkdir build
cd build
cmake ..
make 
mv NPuzzle ..
