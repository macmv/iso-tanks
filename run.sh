#! /usr/bin/sh

bazel build -c dbg --cxxopt='-std=c++17' $1 $2 && cd bazel-bin/$1.runfiles/__main__/ && gdb $1 && cd ../../../
