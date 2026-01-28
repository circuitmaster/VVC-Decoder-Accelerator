#include "IDCT2.hpp"
#include "ap_int.h"
#include <iostream>

int main(int argc, char* argv[]) {
    // here initialize inputs and run hardware function (host simulation, not real hardware run
    // ) and compare with the golden model.

    // hardware simulation
    ap_uint<1024> in1 = 0;
    ap_uint<1024> in2 = 0;

    ap_uint<1024> out1 = 0;
    ap_uint<1024> out2 = 0;

    IDCT2(&in1, &in2, &out1, &out2, 4, 1, 0, 0, 10000);

    for(int i = 0; i < 4; i++) {
        std::cout << "Output1[" << i << "] = " << out1.range((i+1)*32-1, i*32) << std::endl;
    }

    // run golden model

    // compare results
    
    return 0;
}