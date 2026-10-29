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

    //init Vbuddy
    if (init_vbd() == -1) return (-1);

    //init simulation inputs
    top->clk = 1;
    top->rst = 0;  //immediately starts counting from 0

    //run simulation for 300 clock cycles
    for (i=0; i<20; ++i) {
        //inputs change BEFORE clock is toggled and i starts at 0
        //so i=n indicates the start of the (n+1)th cycle 

        top->en = vbdFlag();

        toggle_clk(top, tfp, i);    //function that dumps variables into VSC file and toggles clock
        send_vbd_count(top, i);

        if(Verilated::gotFinish()) exit(0);
    }

    tfp->close();
    close_vbd();
    exit(0);
}