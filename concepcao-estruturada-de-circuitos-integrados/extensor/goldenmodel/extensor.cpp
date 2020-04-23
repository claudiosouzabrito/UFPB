#include <fstream>
#include <iostream>
#include <string>
using namespace std;
int main(){
    ofstream out;
    out.open("../simulation/modelsim/extensor.tv");
    int inp[16];
    int outp[32];
    for (inp[15] = 0; inp[15] < 2; inp[15]++){
        outp[15] = inp[15];
        for(int i = 16; i < 32; i++){
            outp[i] = inp[15];
        }
        for (inp[14] = 0; inp[14] < 2; inp[14]++){
            outp[14] = inp[14];
            for (inp[13] = 0; inp[13] < 2; inp[13]++){
                outp[13] = inp[13];
                for (inp[12] = 0; inp[12] < 2; inp[12]++){
                    outp[12] = inp[12];
                    for (inp[11] = 0; inp[11] < 2; inp[11]++){
                        outp[11] = inp[11];
                        for (inp[10] = 0; inp[10] < 2; inp[10]++){
                            outp[10] = inp[10];
                            for (inp[9] = 0; inp[9] < 2; inp[9]++){
                                outp[9] = inp[9];
                                for (inp[8] = 0; inp[8] < 2; inp[8]++){
                                    outp[8] = inp[8];
                                    for (inp[7] = 0; inp[7] < 2; inp[7]++){
                                        outp[7] = inp[7];
                                        for (inp[6] = 0; inp[6] < 2; inp[6]++){
                                            outp[6] = inp[6];
                                            for (inp[5] = 0; inp[5] < 2; inp[5]++){
                                                outp[5] = inp[5];
                                                for (inp[4] = 0; inp[4] < 2; inp[4]++){
                                                    outp[4] = inp[4];
                                                    for (inp[3] = 0; inp[3] < 2; inp[3]++){
                                                        outp[3] = inp[3];
                                                        for (inp[2] = 0; inp[2] < 2; inp[2]++){
                                                            outp[2] = inp[2];
                                                            for (inp[1] = 0; inp[1] < 2; inp[1]++){
                                                                outp[1] = inp[1];
                                                                for (inp[0] = 0; inp[0] < 2; inp[0]++){
                                                                    outp[0] = inp[0];
                                                                    for(int i = 15; i >= 0; i--){
                                                                        out << inp[i];
                                                                    }
                                                                    out << "_";
                                                                    for(int i = 31; i >= 0; i--){
                                                                        out << outp[i];
                                                                    }
                                                                    out << endl;
                                                                }
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }        
        }
    }
}