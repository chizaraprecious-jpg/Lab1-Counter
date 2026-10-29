#!/bin/bash

cd task4

#cleanup
rm -rf obj_dir
rm -f counter.vcd

echo "Compiling program.."
if verilator -Wall --cc --trace counter.sv bin2bcd.sv top.sv --exe top_tb.cpp \
    -CFLAGS "-I$(realpath ../include)"; then
    echo "Compilation successful"

    echo "Building program..."
    if make -j -C obj_dir/ -f Vcounter.mk Vcounter; then
        echo "Build successful"
        echo "Running program..."
        ~/Documents/iac/lab0-devtools/tools/attach_usb.sh
        obj_dir/Vcounter
        surfer "counter.vcd"

    else
        echo "Build failed"
    fi
    
else
    echo "Compilation failed"
fi