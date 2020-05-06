#include <stdio.h>
#include <stdlib.h>
#include <math.h>

float Funcao (float x, int op){
    if (op == 1)
        return sqrt(1 + pow(x, 3));
    if (op == 2)
        return 1/x;
}

float Trapezios(float a, float b, int n, int op)
{
    int ti = 1;
    float h, xi, yi, sum = 0;

    h = (b - a)/n;

    printf("| i |   xi    |   yi    | ti|\n");
    for(int i = 0; i <= n; i++){
        if(i == 0 || i == n){
            ti = 1;
        }else{
            ti = 2;
        }

        xi = a + (i * h);
        yi = Funcao(xi, op); //funcao
        sum += yi * ti; //somatorio
        printf("| %d | %.5f | %.5f | %d |\n", i, xi, yi, ti);
    }
    return (h * sum)/2;
}

int main ()
{
    float a, b;
    int n, ti = 1, op;

    printf("Digite os valores de a e b.\na: ");
    scanf("%f", &a);
    printf("b: ");
    scanf("%f", &b);
    printf("Digite o n: ");
    scanf("%d", &n);
    printf("Selecione a funcao:\n"
           "1: f(x) = sqrt(1 + (x^3))\n"
           "2: f(x) = 1/x\n");
    scanf("%d", &op);

    printf("\nResultado: %f\n", Trapezios(a, b, n, op));

    return 0;
}
