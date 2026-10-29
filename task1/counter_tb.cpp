#include "Vcounter.h"
#include "verilated.h"
#include "verilated_vcd_c.h"
#include "tb_functions.hpp"

int main(int argc, char **argv, char **en) {
    int i; //counts the number of clock cycles


    Verilated::commandArgs(argc, argv);

    //init top verilog instance
    Vcounter* top = new Vcounter;

    //init trace dump
    Verilated::traceEverOn(true);
    VerilatedVcdC* tfp = new VerilatedVcdC; //trace file pointer (for the trace dump)
    top->trace(tfp, 99);
    tfp->open("counter.vcd");

    //init simulation inputs
    top->clk = 1;
    top->rst = 0;  //immediately starts counting from 0
    top->en = 1;

    //run simulation for 300 clock cycles
    for (i=0; i<300; ++i) {
        //inputs change BEFORE clock is toggled and i starts at 0
        //so i=n indicates the start of the (n+1)th cycle 

        top->rst = (i > 4) && (i % 4 == 1);          //after the 5th cycle, reset is activated every four cycles
        top->en = (i<20);

        toggle_clk(top, tfp, i);                      //function that dumps variables into VSC file and toggles clock
    }

    tfp->close();
    close_vbd();
    exit(0);
}