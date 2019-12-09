#include "../../acc/goldenmodel/acc.h"
#include "../../inv/goldenmodel/inv.h"
#include "../../somador/goldenmodel/somador.h"
#include "../../mux/goldenmodel/mux.h"
int main(){
    int sel0, sel1, clk = 0, clka = 1, a[4], inva[4], mux0[4], mux1[4], soma[4], c_out = 0, s[4], b[4];
    int newac[4];
    FILE *fp;
    fp = fopen("tabela-addac.tv", "w");
 //   fprintf(fp, "sel0_sel1_a_acu_clk_s_newacu\n");
    sel0 = 0;
    sel1 = 0;
    int i,j,k,l,m,n,o,p;
    for(int i = 0; i < 2; i++){
        for(int j = 0; j < 2; j++){
            for(int k = 0; k < 2; k++){
                for(int l = 0; l < 2; l++){
                    for(int m = 0; m < 2; m++){
                        for(int n = 0; n < 2; n++){
                            for(int o = 0; o < 2; o++){
                                for(int p = 0; p < 2; p++){
                                    for(int q = 0; q < 2; q++){
                                        a[0] = i;
                                        a[1] = j;
                                        a[2] = k;
                                        a[3] = l;
                                        b[0] = m;
                                        b[1] = n;
                                        b[2] = o;
                                        b[3] = p;
                                        clk = q;
                                        inv(a, inva);
                                        mux(a, inva, sel0, mux0);
                                        somador(mux0, b, sel0, soma, &c_out);
                                        mux(mux0, soma, sel1, mux1);
                                        acc(clka, clk, mux1, b, newac);
                                        fprintf(fp, "%d", sel0);
                                        fprintf(fp, "_");
                                        fprintf(fp, "%d", sel1);
                                        fprintf(fp, "_");
                                        for(int i = 0; i < 4; i++){
                                            fprintf( fp, "%d", a[i]);
                                        }
                                        fprintf(fp, "_");
                                        for(int i = 0; i < 4; i++){
                                            fprintf( fp, "%d", b[i]);
                                        }
                                        fprintf(fp, "_");
                                        fprintf(fp, "%d", clk);
                                        fprintf(fp, "_");
                                        for(int i = 0; i < 4; i++){
                                            fprintf( fp, "%d", mux1[i]);
                                        }
                                        fprintf(fp, "_");
                                        for(int i = 0; i < 4; i++){
                                            fprintf( fp, "%d", newac[i]);
                                        }
                                        fprintf(fp, "\n");
                                        clka = clk;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
                           
    sel0 = 0;
    sel1 = 1;
    for(int i = 0; i < 2; i++){
        for(int j = 0; j < 2; j++){
            for(int k = 0; k < 2; k++){
                for(int l = 0; l < 2; l++){
                    for(int m = 0; m < 2; m++){
                        for(int n = 0; n < 2; n++){
                            for(int o = 0; o < 2; o++){
                                for(int p = 0; p < 2; p++){
                                    for(int q = 0; q < 2; q++){
                                        a[0] = i;
                                        a[1] = j;
                                        a[2] = k;
                                        a[3] = l;
                                        b[0] = m;
                                        b[1] = n;
                                        b[2] = o;
                                        b[3] = p;
                                        clk = q;
                                        inv(a, inva);
                                        mux(a, inva, sel0, mux0);
                                        somador(mux0, b, sel0, soma, &c_out);
                                        mux(mux0, soma, sel1, mux1);
                                        acc(clka, clk, mux1, b, newac);
                                        fprintf(fp, "%d", sel0);
                                        fprintf(fp, "_");
                                        fprintf(fp, "%d", sel1);
                                        fprintf(fp, "_");
                                        for(int i = 0; i < 4; i++){
                                            fprintf( fp, "%d", a[i]);
                                        }
                                        fprintf(fp, "_");
                                        for(int i = 0; i < 4; i++){
                                            fprintf( fp, "%d", b[i]);
                                        }
                                        fprintf(fp, "_");
                                        fprintf(fp, "%d", clk);
                                        fprintf(fp, "_");
                                        for(int i = 0; i < 4; i++){
                                            fprintf( fp, "%d", mux1[i]);
                                        }
                                        fprintf(fp, "_");
                                        for(int i = 0; i < 4; i++){
                                            fprintf( fp, "%d", newac[i]);
                                        }
                                        fprintf(fp, "\n");
                                        clka = clk;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    sel0 = 1;
    sel1 = 0;
    for(int i = 0; i < 2; i++){
        for(int j = 0; j < 2; j++){
            for(int k = 0; k < 2; k++){
                for(int l = 0; l < 2; l++){
                    for(int m = 0; m < 2; m++){
                        for(int n = 0; n < 2; n++){
                            for(int o = 0; o < 2; o++){
                                for(int p = 0; p < 2; p++){
                                    for(int q = 0; q < 2; q++){
                                        a[0] = i;
                                        a[1] = j;
                                        a[2] = k;
                                        a[3] = l;
                                        b[0] = m;
                                        b[1] = n;
                                        b[2] = o;
                                        b[3] = p;
                                        clk = q;
                                        inv(a, inva);
                                        mux(a, inva, sel0, mux0);
                                        somador(mux0, b, sel0, soma, &c_out);
                                        mux(mux0, soma, sel1, mux1);
                                        acc(clka, clk, mux1, b, newac);
                                        fprintf(fp, "%d", sel0);
                                        fprintf(fp, "_");
                                        fprintf(fp, "%d", sel1);
                                        fprintf(fp, "_");
                                        for(int i = 0; i < 4; i++){
                                            fprintf( fp, "%d", a[i]);
                                        }
                                        fprintf(fp, "_");
                                        for(int i = 0; i < 4; i++){
                                            fprintf( fp, "%d", b[i]);
                                        }
                                        fprintf(fp, "_");
                                        fprintf(fp, "%d", clk);
                                        fprintf(fp, "_");
                                        for(int i = 0; i < 4; i++){
                                            fprintf( fp, "%d", mux1[i]);
                                        }
                                        fprintf(fp, "_");
                                        for(int i = 0; i < 4; i++){
                                            fprintf( fp, "%d", newac[i]);
                                        }
                                        fprintf(fp, "\n");
                                        clka = clk;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    sel0 = 1;
    sel1 = 1;
    for(int i = 0; i < 2; i++){
        for(int j = 0; j < 2; j++){
            for(int k = 0; k < 2; k++){
                for(int l = 0; l < 2; l++){
                    for(int m = 0; m < 2; m++){
                        for(int n = 0; n < 2; n++){
                            for(int o = 0; o < 2; o++){
                                for(int p = 0; p < 2; p++){
                                    for(int q = 0; q < 2; q++){
                                        a[0] = i;
                                        a[1] = j;
                                        a[2] = k;
                                        a[3] = l;
                                        b[0] = m;
                                        b[1] = n;
                                        b[2] = o;
                                        b[3] = p;
                                        clk = q;
                                        inv(a, inva);
                                        mux(a, inva, sel0, mux0);
                                        somador(mux0, b, sel0, soma, &c_out);
                                        mux(mux0, soma, sel1, mux1);
                                        acc(clka, clk, mux1,b, newac);
                                        fprintf(fp, "%d", sel0);
                                        fprintf(fp, "_");
                                        fprintf(fp, "%d", sel1);
                                        fprintf(fp, "_");
                                        for(int i = 0; i < 4; i++){
                                            fprintf( fp, "%d", a[i]);
                                        }
                                        fprintf(fp, "_");
                                        for(int i = 0; i < 4; i++){
                                            fprintf( fp, "%d", b[i]);
                                        }
                                        fprintf(fp, "_");
                                        fprintf(fp, "%d", clk);
                                        fprintf(fp, "_");
                                        for(int i = 0; i < 4; i++){
                                            fprintf( fp, "%d", mux1[i]);
                                        }
                                        fprintf(fp, "_");
                                        for(int i = 0; i < 4; i++){
                                            fprintf( fp, "%d", newac[i]);
                                        }
                                        fprintf(fp, "\n");
                                        clka = clk;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    fclose(fp);
    return 0;
}