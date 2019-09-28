#include <genlib.h>

int main(void){
    GENLIB_DEF_LOFIG("ff_l_m_e");

    GENLIB_LOCON("a",IN,"a");
    GENLIB_LOCON("ck",IN,"ck");
    GENLIB_LOCON("q",OUT,"q");
    GENLIB_LOCON("vdd",IN,"vdd");
    GENLIB_LOCON("vss",IN,"vss");

    GENLIB_LOINSE("la_l", "la_m",
    "a=>a",
    "ck=>ck_m,
    "q=>q_m",
    "vdd=>vdd",
    "vss=>vss",
    NULL);

    GENLIB_LOINSE("la_l", "la_e",
    "a=>q_m",
    "ck=>ck_e,
    "q=>q",
    "vdd=>vdd",
    "vss=>vss",
    NULL);

    GENLIB_SAVE_LOFIG();

    

    return 0;
}