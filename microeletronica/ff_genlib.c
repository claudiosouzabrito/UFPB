#include <genlib.h>

int main(void){


   GENLIB_DEF_LOFIG("ff_genlib");
   


   GENLIB_LOCON("a", IN, "a");
   GENLIB_LOCON("clk_m", IN, "clk_m");
   GENLIB_LOCON("clk_e", IN, "clk_e");
   GENLIB_LOCON("q", OUT, "q");
   GENLIB_LOCON("vdd", IN, "vdd");
   GENLIB_LOCON("vss", IN, "vss");


   GENLIB_LOINSE("la_1", "la_m",
   "a => a",
   "clk => clk_m",
   "q => q_m",
   "vdd => vdd",
   "vss => vss",
   NULL);

   GENLIB_LOINSE("la_1", "la_e",
   "a => q_m",
   "clk => clk_e",
   "q => q",
   "vdd => vdd",
   "vss => vss",
   NULL);


   GENLIB_SAVE_LOFIG();

   return 0;
}
