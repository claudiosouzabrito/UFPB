#include "../acc/goldenmodel/acc.h"
#include "../inv/goldenmodel/inv.h"
#include "../somador/goldenmodel/somador.h"
#include "../mux/goldenmodel/mux.h"
int main(){
    int a,b,c,d,e;
    inv(a);
    acc(a,b,c,d);
    mux(a,b,c);
    somador(a,b,c,d,e);
    return 0;
}