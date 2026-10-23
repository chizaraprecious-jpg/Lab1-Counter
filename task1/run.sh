#!/bin/bash

cd task1

#cleanup
rm -rf obj_dir
rm -f counter.vcd

echo "Compiling program.."
if verilator -Wall --cc --trace counter.sv --exe counter_tb.cpp \
    -CFLAGS "-I$(realpath ../include)"; then
    echo "Compilation successful"

    echo "Building program..."
    if make -j -C obj_dir/ -f Vcounter.mk Vcounter; then
        echo "Build successful"
        echo "Running program..."
        obj_dir/Vcounter
        surfer "counter.vcd"

    else
        echo "Build failed"
    fi
    
else
    echo "Compilation failed"
fi