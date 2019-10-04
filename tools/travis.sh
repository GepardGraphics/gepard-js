#!/bin/bash

# Copyright (C) 2019, Gepard Graphics
# Copyright (C) 2019, Kristof Kosztyo <kkristof@inf.u-szeged.hu>
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:
#
# 1. Redistributions of source code must retain the above copyright notice, this
#    list of conditions and the following disclaimer.
# 2. Redistributions in binary form must reproduce the above copyright notice,
#    this list of conditions and the following disclaimer in the documentation
#   and/or other materials provided with the distribution.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
# ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
# WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
# DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
# ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
# (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
# LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
# ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
# (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
# SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.


mkdir thirdparty
export PROJECT_ROOT=`pwd`

export GEPARD_DIR=thirdparty/gepard
git clone https://github.com/GepardGraphics/gepard.git $GEPARD_DIR
cd $GEPARD_DIR
cmake -Bbuild -H.
make -C build
export GEPARD_INSTALL_DIR=$PROJECT_ROOT/$GEPARD_DIR/build
cd $PROJECT_ROOT

export JERRYSCRIPT_DIR=thirdparty/jerryscript
export JERRYSCRIPT_INSTALL_DIR=$PROJECT_ROOT/thirdparty/jerryscript-install
git clone https://github.com/jerryscript-project/jerryscript.git $JERRYSCRIPT_DIR
git checkout tags/v2.0
cd $JERRYSCRIPT_DIR
python tools/build.py --install $JERRYSCRIPT_INSTALL_DIR --jerry-ext ON
cd $PROJECT_ROOT

cmake -Bbuild -H. -DGEPARD_INSTALL_DIR=$GEPARD_INSTALL_DIR -DJERRYSCRIPT_INSTALL_DIR=$JERRYSCRIPT_INSTALL_DIR
make -C build
pwd
echo $PROJECT_ROOT
echo $GEPARD_INSTALL_DIR
echo $JERRYSCRIPT_INSTALL_DIR
