#include "genlib.h"

int main(void){
    GENLIB_DEF_LOFIG("la_1_genlib");

    GENLIB_LOCON("a",IN,"a");
    GENLIB_LOCON("ck",IN,"ck");
    GENLIB_LOCON("q",OUT,"q");
    GENLIB_LOCON("vdd",IN,"vdd");
    GENLIB_LOCON("vss",IN,"vss");

    GENLIB_LOINS("inv_x1","inv_1","b","q","vdd","vss",NULL);
    GENLIB_LOINS("inv_x1","inv_2","q","q_b","vdd","vss",NULL);
    GENLIB_LOINS("mx2_x2","mux","ck","q_b","a","b","vdd","vss",NULL);
    GENLIB_SAVE_LOFIG();

    return 0;
}