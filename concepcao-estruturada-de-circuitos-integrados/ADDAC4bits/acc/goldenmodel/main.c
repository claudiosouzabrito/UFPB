#include "acc.h"
int main(){
    int i,j,k,l,m,n,o,p;
    int a[4], b[4], c, ca = 1, s[4];
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
                                        c = q;
                                        acc(ca, c, a, b, s);
                                        ca = c;
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