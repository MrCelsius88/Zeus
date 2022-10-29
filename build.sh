#!/bin/bash

code="$PWD"
opts=-g
linker_opts="-lglfw3 -lGL -lX11 -lpthread -lXrandr -lXi -ldl"
cd build > /dev/null
g++ $opts $code/src/main.c $linker_opts -o DungeonMaster
cd $code > /dev/null
