#include "../../acc/goldenmodel/acc.h"
#include "../../inv/goldenmodel/inv.h"
#include "../../somador/goldenmodel/somador.h"
#include "../../mux/goldenmodel/mux.h"
int main(){
    int sel0, sel1, clk = 0, clka = 1, a = 0, mux0 = 0, mux1 = 0, soma = 0, c_out = 0, s, ac = 0;
    int newac;
    FILE *fp;
    fp = fopen("../simulation/modelsim/tabela-addac.tv", "w");
    fprintf(fp, "sel0_sel1_a_clk_acu_saida\n");
    sel0 = 0;
    sel1 = 0;
    for(a = 0; a < 2; a++){
        for(ac = 0; ac < 2; ac++){
            for(clk = 0; clk < 2; clk++){
                mux0 = mux(a, inv(a), sel0);
                somador(mux0, ac, sel0, &soma, &c_out);
                mux1 = mux(mux0, soma, sel1);
                newac = acc(clka, clk, mux1, ac);
                fprintf(fp, "%d_%d_%d_%d_%d_%d_%d\n", sel0, sel1, a, ac, clk, mux1, newac);
                clka = clk;    
            }
            
        }
        
    }
    sel0 = 0;
    sel1 = 1;
    for(a = 0; a < 2; a++){
        for(ac = 0; ac < 2; ac++){
            for(clk = 0; clk < 2; clk++){
                mux0 = mux(a, inv(a), sel0);
                somador(mux0, ac, sel0, &soma, &c_out);
                mux1 = mux(mux0, soma, sel1);
                newac = acc(clka, clk, mux1, ac);
                fprintf(fp, "%d_%d_%d_%d_%d_%d_%d\n", sel0, sel1, a, ac, clk, mux1, newac);
                clka = clk;
            }
        }
        
    }
    sel0 = 1;
    sel1 = 0;
    for(a = 0; a < 2; a++){
        for(ac = 0; ac < 2; ac++){
            for(clk = 0; clk < 2; clk++){
                mux0 = mux(a, inv(a), sel0);
                somador(mux0, ac, sel0, &soma, &c_out);
                mux1 = mux(mux0, soma, sel1);
                newac = acc(clka, clk, mux1, ac);
                fprintf(fp, "%d_%d_%d_%d_%d_%d_%d\n", sel0, sel1, a, ac, clk, mux1, newac);
                clka = clk;   
            }
        }
    }
    sel0 = 1;
    sel1 = 1;
    for(a = 0; a < 2; a++){
        for(ac = 0; ac < 2; ac++){
            for(clk = 0; clk < 2; clk++){
                mux0 = mux(a, inv(a), sel0);
                somador(mux0, ac, sel0, &soma, &c_out);
                mux1 = mux(mux0, soma, sel1);
                newac = acc(clka, clk, mux1, ac);
                fprintf(fp, "%d_%d_%d_%d_%d_%d_%d\n", sel0, sel1, a, ac, clk, mux1, newac);
                clka = clk;   
            }
        }
    }
    fclose(fp);
    return 0;
}