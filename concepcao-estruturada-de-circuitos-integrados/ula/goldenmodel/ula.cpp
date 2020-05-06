#include <fstream>
#include <iostream>
#include <string>
#include <string.h>
using namespace std;

void somador(int a, int b, int c, int *s, int *o){
    int d;
    d = a+b+c;
    switch (d){
        case 0:
            *s = 0;
            *o = 0;
            break;
        case 1:
            *s = 1;
            *o = 0;
            break;
        case 2:
            *s = 0;
            *o = 1;
            break;
        default:
            *s = 1;
            *o = 1;
            break;
    }
    
}

void subtrator(int a, int b, int c, int *s, int *o){
    if(a){
        if(b){
            if(c){
                *s = 1;
                *o = 1;
            }
            else{
                *s = 0;
                *o = 0;
            }
        }
        else{
            if(c){
                *s = 0;
                *o = 0;
            }
            else{
                *s = 1;
                *o = 0;
            }
        }
    }
    else{
        if(b){
            if(c){
                *s = 0;
                *o = 1;
            }
            else{
                *s = 1;
                *o = 1;
            }
        }
        else{
            if(c){
                *s = 1;
                *o = 1;
            }
            else{
                *s = 0;
                *o = 0;
            }
        }
    }
    
}



int main(){
    ofstream out;
    out.open("../simulation/modelsim/ula.tv");
    string funct, aluctrl;
    int addsub;
    int  ci = 0, co = 0,  i;
    int aluop[2];
    int a[32] = {0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1};
    int b[32] = {1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0};
    int aluout[32] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    for(aluop[0] = 0; aluop[0] < 2; aluop[0]++){
        for(aluop[1] = 0; aluop[1] < 2; aluop[1]++){
            funct.assign("100000");
            aluctrl.assign("100"); //ADD
            if(aluop[0] == 0 && aluop[1] == 1){
                addsub = 1;
                subtrator( a[0], b[0], addsub, &aluout[0], &ci);
                for(  i = 1; i < 32; i++){
                    subtrator( a[i], b[i], ci, &aluout[i], &ci);
                }
            }
            else{ 
                addsub = 0;
                somador( a[0], b[0], addsub, &aluout[0], &ci);
                for(  i = 1; i < 32; i++){
                    somador( a[i], b[i], ci, &aluout[i], &ci);
                }
            }
            out << aluop[0] << aluop[1] << "_" << funct << "_";
            for(  i = 31; i >= 0; i--) out << a[i];
            out << "_";
            for(  i = 31; i >= 0; i--) out << b[i];
            out << "_";
            for(  i = 31; i >= 0; i--) out << aluout[i];
            out << endl;
            ci = 0;
         ////////////////////////////////////////////////////////
            funct.assign("100010");
            addsub = 1;
            aluctrl.assign("100"); // SUB
            if((aluop[0] == 0 && aluop[1] == 0)){
                cout << aluop[0] << aluop[1] << "_" << funct << endl;
                addsub = 0;
                somador( a[0], b[0], addsub, &aluout[0], &ci);
                for(  i = 1; i < 32; i++){
                    somador( a[i], b[i], ci, &aluout[i], &ci);
                }
            } 
            else{
                addsub = 1;
                subtrator( a[0], b[0], addsub, &aluout[0], &ci);
                for(  i = 1; i < 32; i++){
                    subtrator( a[i], b[i], ci, &aluout[i], &ci);
                }
            } 
            
            out << aluop[0] << aluop[1] << "_" << funct << "_";
            for(  i = 31; i >= 0; i--) out << a[i];
            out << "_";
            for(  i = 31; i >= 0; i--) out << b[i];
            out << "_";
            for(  i = 31; i >= 0; i--) out << aluout[i];
            out << endl;
            ci = 0;
            ////////////////////////////////////////////////////////
            funct.assign("100100");
            aluctrl.assign("000"); // AND
            
            if((aluop[0] == 0 && aluop[1] == 0)){
                addsub = 0;
                somador( a[0], b[0], addsub, &aluout[0], &ci);
                for(  i = 1; i < 32; i++){
                    somador( a[i], b[i], ci, &aluout[i], &ci);
                }
            } 
            else if(aluop[0] == 0 && aluop[1] == 1){
                addsub = 1;
                subtrator( a[0], b[0], addsub, &aluout[0], &ci);
                for(  i = 1; i < 32; i++){
                    subtrator( a[i], b[i], ci, &aluout[i], &ci);
                }
            }  
            else for(  i = 0; i < 31; i++) aluout[i] = a[i]*b[i];
            out << aluop[0] << aluop[1] << "_" << funct << "_";
            for(  i = 31; i >= 0; i--) out << a[i];
            out << "_";
            for(  i = 31; i >= 0; i--) out << b[i];
            out << "_";
            for(  i = 31; i >= 0; i--) out << aluout[i];
            out << endl;
            ci = 0;
            ///////////////////////////////////////////////////
            funct.assign("100101");
            aluctrl.assign("001"); // OR
            if((aluop[0] == 0 && aluop[1] == 0)){
                addsub = 0;
                somador( a[0], b[0], addsub, &aluout[0], &ci);
                for(  i = 1; i < 32; i++){
                    somador( a[i], b[i], ci, &aluout[i], &ci);
                }
            } 
            else if((aluop[0] == 0 && aluop[1] == 1)){
                addsub = 1;
                subtrator( a[0], b[0], addsub, &aluout[0], &ci);
                for(  i = 1; i < 32; i++){
                    subtrator( a[i], b[i], ci, &aluout[i], &ci);
                }
            }  
            else for(  i = 0; i < 32; i++){
                aluout[i] = a[i]+b[i];
                if(aluout[i] > 1) aluout[i] = 1;
            } 
            out << aluop[0] << aluop[1] << "_" << funct << "_";
            for(  i = 31; i >= 0; i--) out << a[i];
            out << "_";
            for(  i = 31; i >= 0; i--) out << b[i];
            out << "_";
            for(  i = 31; i >= 0; i--) out << aluout[i];
            out << endl;
            ci = 0;
            ////////////////////////////////////////////////////////
            funct.assign("100110");
            aluctrl.assign("010"); // NOR
            
            if((aluop[0] == 0 && aluop[1] == 0)){
                addsub = 0;
                somador( a[0], b[0], addsub, &aluout[0], &ci);
                for(  i = 1; i < 32; i++){
                    somador( a[i], b[i], ci, &aluout[i], &ci);
                }
            } 
            else if((aluop[0] == 0 && aluop[1] == 1)){
                addsub = 1;
                subtrator( a[0], b[0], addsub, &aluout[0], &ci);
                for(  i = 1; i < 32; i++){
                    subtrator( a[i], b[i], ci, &aluout[i], &ci);
                }
            }  
            else  for(  i = 0; i < 32; i++){
                aluout[i] = a[i]+b[i];
                if(aluout[i] >= 1) aluout[i] = 0;
                else aluout[i] = 1;
            }
            out << aluop[0] << aluop[1] << "_" << funct << "_";
            for(  i = 31; i >= 0; i--) out << a[i];
            out << "_";
            for(  i = 31; i >= 0; i--) out << b[i];
            out << "_";
            for(  i = 31; i >= 0; i--) out << aluout[i];
            out << endl;
            ci = 0;
            ////////////////////////////////////////////////////
            funct.assign("100111");
            aluctrl.assign("011"); // XOR
            if((aluop[0] == 0 && aluop[1] == 0)){
                addsub = 0;
                somador( a[0], b[0], addsub, &aluout[0], &ci);
                for(  i = 1; i < 32; i++){
                    somador( a[i], b[i], ci, &aluout[i], &ci);
                }
            } 
            else if((aluop[0] == 0 && aluop[1] == 1)){
                addsub = 1;
                subtrator( a[0], b[0], addsub, &aluout[0], &ci);
                for(  i = 1; i < 32; i++){
                    subtrator( a[i], b[i], ci, &aluout[i], &ci);
                }
            }  
            else for(  i = 0; i < 32; i++){
                if(a[i] == b[i]) aluout[i] = 0;
                else aluout[i] = 1;
            }
            out << aluop[0] << aluop[1] << "_" << funct << "_";
            for(  i = 31; i >= 0; i--) out << a[i];
            out << "_";
            for(  i = 31; i >= 0; i--) out << b[i];
            out << "_";
            for(  i = 31; i >= 0; i--) out << aluout[i];
            out << endl;
            ci = 0;
            /////////////////////////////////////////////////////
            funct.assign("101010");
            aluctrl.assign("101"); // SLT
            if((aluop[0] == 0 && aluop[1] == 0)){
                addsub = 0;
                somador( a[0], b[0], addsub, &aluout[0], &ci);
                for(  i = 1; i < 32; i++){
                    somador( a[i], b[i], ci, &aluout[i], &ci);
                }
            } 
            else if((aluop[0] == 0 && aluop[1] == 1)){
                addsub = 1;
                subtrator( a[0], b[0], addsub, &aluout[0], &ci);
                for(  i = 1; i < 32; i++){
                    subtrator( a[i], b[i], ci, &aluout[i], &ci);
                }
            }  
            else for(  i = 0; i < 32; i++){
                if(a[i] < b[i]) aluout[i] = 1;
                else aluout[i] = 0;
            }
            out << aluop[0] << aluop[1] << "_" << funct << "_";
            for(  i = 31; i >= 0; i--) out << a[i];
            out << "_";
            for(  i = 31; i >= 0; i--) out << b[i];
            out << "_";
            for(  i = 31; i >= 0; i--) out << aluout[i];
            out << endl;
            ci = 0;
        }
    }    
}