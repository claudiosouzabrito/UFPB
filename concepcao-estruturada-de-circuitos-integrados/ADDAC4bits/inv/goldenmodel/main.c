#include "inv.h"
int main(){
    int i,j,k,l;
    int a[4],saia[4];
    for(int i = 0; i < 2; i++){
        for(int j = 0; j < 2; j++){
            for(int k = 0; k < 2; k++){
                for(int l = 0; l < 2; l++){
                    a[0] = i;
                    a[1] = j;
                    a[2] = k;
                    a[3] = l;
                    inv(a,saia);
                }
            }
        }
    }
}