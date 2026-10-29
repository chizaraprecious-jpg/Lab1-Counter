#!/bin/bash

cd task4

#cleanup
rm -rf obj_dir
rm -f top.vcd

echo "Compiling program.."
if verilator -Wall --cc --trace counter.sv bin2bcd.sv top.sv --exe top_tb.cpp \
    --top-module top \
    -CFLAGS "-I$(realpath ../include)"; then
    echo "Compilation successful"

    echo "Building program..."
    if make -j -C obj_dir/ -f Vtop.mk Vtop; then
        echo "Build successful"
        echo "Running program..."
        ~/Documents/iac/lab0-devtools/tools/attach_usb.sh
        obj_dir/Vtop
        surfer "top.vcd"

    else
        echo "Build failed"
    fi
    
else
    echo "Compilation failed"
fi