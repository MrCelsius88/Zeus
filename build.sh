#!/bin/bash

code="$PWD"
opts=-g
linker_opts="-lglfw3 -lGL -lX11 -lpthread -lXrandr -lXi -ldl -lm"
cd build > /dev/null
gcc $opts $code/src/main.c $linker_opts -o DungeonMaster
cd $code > /dev/null
