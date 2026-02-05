#include "IDCT2.hpp"
//#include "IDCT2_new.hpp"
#include "ap_int.h"
#include <iostream>
#include "originals.hpp"

int main(int argc, char* argv[]) {
    // here initialize inputs and run hardware function (host simulation, not real hardware run
    // ) and compare with the golden model.

    // hardware simulation
    ap_uint<1024> in1 = 10;
    ap_uint<1024> in2 = 10;

    ap_uint<1024> out1 = 2;
    ap_uint<1024> out2 = 2;

    ap_uint<1024> in1_o = in1;
    ap_uint<1024> out1_o = 0;



    IDCT2(&in1, &in2, &out1, &out2, 64, 1, 1, 0, 10000);

    for(int i = 0; i < 4; i++) {
        std::cout << "Output1[" << i << "] = " << out1.range((i+1)*32-1, i*32) << std::endl;
    }

    // run golden model
    fastInverseDCT2_B64(reinterpret_cast<const int*>(&in1_o), reinterpret_cast<int*>(&out1_o), 1, 4, 0, 0, 0, 10000);
    for(int i = 0; i < 4; i++) {
        std::cout << "Output1_o[" << i << "] = " << out1_o.range((i+1)*32-1, i*32) << std::endl;
    }
    // compare results
    
    return 0;
}