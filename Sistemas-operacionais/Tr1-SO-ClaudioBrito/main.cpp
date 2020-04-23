#include <iostream>
#include <string>
#include <fstream>
#include "classe.h"
#include <vector>
using namespace std;
int main(){
    ifstream in;
    in.open("entrada");
    string linha, l1, l2;
    int numlinha = 0, i = 0, j = 0, k = 1;
    while(getline(in, linha)) numlinha++;
    in.close();
    in.open("entrada");
    process processo[numlinha+1];
    int salvdura[numlinha+1];
    while(getline(in, linha)){
    //    processo[k].flag = 0;
        processo[k].tespera = 0;
        while(linha[i] != ' ') i++;
        l1 = linha.substr(0, i);
        processo[k].chegada = stoi(l1);
        j = ++i;
        i = 0;
        while(linha[i] != '\0') i++;
        l2 = linha.substr(j, i-j+1);
        processo[k].duracao = stoi(l2);
        salvdura[k] = processo[k].duracao;
        i = 0;
        k++;
    }
    j = 0;
    k = 0;
    vector<int> espera;
    int flagfim = 0, t = 0, flaglivre = 1, cooratual, contador = 0, atual;

    //FCFS
//    cout << "*******FCFS*******\n";
    while(1){
    //    cout << "t = " << t << endl;
        for(int i = 1; i < numlinha+1; i++) if(processo[i].chegada == t){
        //    cout << "entrando: " << i << endl;
            espera.insert(espera.begin(),i);
        //    for(int i = 0; i < espera.size(); i++) cout << espera[i] << " ";
        //    cout << endl; 
        } 
        if(flaglivre && !espera.empty()){
            cooratual = espera.size() - 1;
        //    cout << "coordenada atual: " << cooratual << endl;
            atual = espera[cooratual];
        //    cout << "processo entrando: " << atual << endl; 
            processo[atual].tespera = t - processo[atual].chegada;
            processo[atual].treposta = processo[atual].tespera;
            espera.pop_back();
        //    for(int i = 0; i < espera.size(); i++) cout << espera[i] << " ";
        //    cout << endl;
            flaglivre = 0;
        }
        else processo[atual].duracao--;
        if(!processo[atual].duracao){
        //    cout << "processo " << atual << " acabou\n";
            processo[atual].tretorno = t - processo[atual].chegada;
            contador++;
            flaglivre = 1;
            if(contador == numlinha) break;
            if(!espera.empty()){
                cooratual = espera.size() - 1;
            //    cout << "coordenada atual: " << cooratual << endl;
                atual = espera[cooratual];
            //    cout << "processo entrando: " << atual << endl;
                processo[atual].tespera = t - processo[atual].chegada;
                processo[atual].treposta = processo[atual].tespera;
                espera.pop_back();
            //    for(int i = 0; i < espera.size(); i++) cout << espera[i] << " ";
            //    cout << endl; 
                flaglivre = 0;
            }
        }
    //    cout << "contador: " << contador < endl;
        t++;
    }
    double totalresp = 0, totalret = 0, totalesp = 0;
    for(i = 1; i < numlinha + 1; i++){
        totalresp += processo[i].treposta;
        totalret += processo[i].tretorno;
        totalesp += processo[i].tespera;
    }
    printf("FCFS %.1lf %.1lf %.1lf\n", totalret/numlinha, totalresp/numlinha, totalesp/numlinha);
    
    //ZERANDO
    for(int i = 1; i < numlinha+1; i++){
        processo[i].tespera = 0;
        processo[i].treposta = 0;
        processo[i].tretorno = 0;
        processo[i].duracao = salvdura[i];
    } 
    flagfim = 0; t = 0; flaglivre = 1; cooratual = 0; contador = 0; atual = 0;
    
    //SJF
//    cout << "*******SJS********\n";
    vector<int>::iterator pt;    
    
    int maior = 0;
    for(int i = 1; i < numlinha+1; i++) if(maior < processo[i].duracao) maior = processo[i].duracao;
    
    int flag1vez = 1;
    while(1){
    //    cout << "t = " << t << " " << flag1vez << endl;
        for(int i = 1; i < numlinha+1; i++) if(processo[i].chegada == t){
        //    cout << "entrando: " << i << endl;
            espera.insert(espera.begin(),i);
        //    for(int i = 0; i < espera.size(); i++) cout << espera[i] << " ";
        //    cout << endl; 
        } 
        if(flaglivre && !espera.empty()){
            for(int i = 0; i < espera.size(); i++) {
                if(flag1vez){
                    atual = espera[i];
                    cooratual = i;
                    flag1vez = 0; 
                }                
                else if(processo[espera[i]].duracao < processo[atual].duracao){
                    atual = espera[i];
                    cooratual = i;
                }
            }
        //    cout << "coordenada atual: " << cooratual << endl;
        //    cout << "processo entrando: " << atual << endl; 
            processo[atual].tespera = t - processo[atual].chegada;
            processo[atual].treposta = processo[atual].tespera;
            pt = espera.begin();
            for(int i = 0; i != cooratual; i++) pt++;
            espera.erase(pt);
        //    for(int i = 0; i < espera.size(); i++) cout << espera[i] << " ";
        //    cout << endl;
            flaglivre = 0;
        }
        else processo[atual].duracao--;
        if(!processo[atual].duracao){
        //    cout << "processo " << atual << " acabou\n";
            processo[atual].tretorno = t - processo[atual].chegada;
            contador++;
            flaglivre = 1;
            if(contador == numlinha) break;
            flag1vez = 1;
            if(!espera.empty()){
                for(int i = 0; i < espera.size(); i++) {
                    if(flag1vez){
                    atual = espera[i];
                    cooratual = i;
                    flag1vez = 0; 
                    }                
                    else if(processo[espera[i]].duracao < processo[atual].duracao){
                        atual = espera[i];
                        cooratual = i;
                    }
                }
            //    cout << "coordenada atual: " << cooratual << endl;
            //    cout << "processo entrando: " << atual << endl; 
                processo[atual].tespera = t - processo[atual].chegada;
                processo[atual].treposta = processo[atual].tespera;
                pt = espera.begin();
                for(int i = 0; i != cooratual; i++) pt++;
                espera.erase(pt);
            //    for(int i = 0; i < espera.size(); i++) cout << espera[i] << " ";
            //    cout << endl;
                flaglivre = 0;
            }
        }
        t++;
    }
    totalresp = 0; totalret = 0; totalesp = 0;
    for(i = 1; i < numlinha + 1; i++){
        totalresp += processo[i].treposta;
        totalret += processo[i].tretorno;
        totalesp += processo[i].tespera;
    }
    printf("SJF %.1lf %.1lf %.1lf\n", totalret/numlinha, totalresp/numlinha, totalesp/numlinha);

    //ZERANDO
    for(int i = 1; i < numlinha+1; i++){
        processo[i].tespera = 0;
        processo[i].treposta = 0;
        processo[i].tretorno = 0;
        processo[i].duracao = salvdura[i];
        processo[i].pvez = 1;
    } 
    flagfim = 0; t = 0; flaglivre = 1; cooratual = 0; contador = 0; atual = 0;
    processo[atual].duracao = -1;
    //RR
//    cout << "*******RR*******\n";
    int RR = 2;
    while(1){
    //    cout << "t = " << t << endl;
        for(int i = 1; i < numlinha+1; i++) if(processo[i].chegada == t){
        //    cout << "entrando: " << i << endl;
            espera.insert(espera.begin(),i);
        //    for(int i = 0; i < espera.size(); i++) cout << espera[i] << " ";
        //    cout << endl; 
        } 
        if(flaglivre && !espera.empty()){
            cooratual = espera.size() - 1;
        //    cout << "coordenada atual: " << cooratual << endl;
            atual = espera[cooratual];
        //    cout << "processo entrando: " << atual << endl; 
            RR = 2;
        //    processo[atual].tespera += t - processo[atual].chegada;
            if(processo[atual].pvez){
                processo[atual].treposta = t - processo[atual].chegada;
                processo[atual].pvez = 0;
            }
            espera.pop_back();
        //    for(int i = 0; i < espera.size(); i++) cout << espera[i] << " ";
        //    cout << endl;
            flaglivre = 0;
        }
        else {
            processo[atual].duracao--;
            RR--;
        }
        if(!processo[atual].duracao){
        //    cout << "processo " << atual << " acabou\n";
            processo[atual].tretorno = t - processo[atual].chegada;
            contador++;
            flaglivre = 1;
            if(contador == numlinha) break;
            if(!espera.empty()){
                cooratual = espera.size() - 1;
            //    cout << "coordenada atual: " << cooratual << endl;
                atual = espera[cooratual];
            //    cout << "processo entrando: " << atual << endl; 
            //    processo[atual].tespera += t - processo[atual].chegada;
                if(processo[atual].pvez){
                    processo[atual].treposta = t - processo[atual].chegada;
                    processo[atual].pvez = 0;
                }
                espera.pop_back();
            //    for(int i = 0; i < espera.size(); i++) cout << espera[i] << " ";
            //    cout << endl;
                flaglivre = 0;
            }
            RR = 2;
        }
        else if(!RR){
        //    cout << "RR acabou...\n";
            if(processo[atual].duracao > 0){
            //    cout << "entrando: " << atual << " com duracao de: " << processo[atual].duracao<< endl;
                espera.insert(espera.begin(),atual);
            //    for(int i = 0; i < espera.size(); i++) cout << espera[i] << " ";
            //    cout << endl;
            }
            if(!espera.empty()){
                cooratual = espera.size() - 1;
            //    cout << "coordenada atual: " << cooratual << endl;
                atual = espera[cooratual];
            //    cout << "processo entrando: " << atual << endl; 
                RR = 2;
            //    processo[atual].tespera += t - processo[atual].chegada;
                if(processo[atual].pvez){
                    processo[atual].treposta = t - processo[atual].chegada;
                    processo[atual].pvez = 0;
                }
                espera.pop_back();
            //    for(int i = 0; i < espera.size(); i++) cout << espera[i] << " ";
            //    cout << endl;
                flaglivre = 0;
            }
        }
        for(int i = 0; i < espera.size(); i++) processo[espera[i]].tespera++;
    //    cout << "contador: " << contador << endl;
        t++;
    }
    totalresp = 0, totalret = 0, totalesp = 0;
    for(i = 1; i < numlinha + 1; i++){
        totalresp += processo[i].treposta;
        totalret += processo[i].tretorno;
    //    cout << i << ": " << processo[i].tretorno << endl;
    //    cout << i << ": " << processo[i].treposta << endl;
    //    cout << i << ": " << processo[i].tespera << endl;
        totalesp += processo[i].tespera;
    }
    printf("RR %.1lf %.1lf %.1lf\n", totalret/numlinha, totalresp/numlinha, totalesp/numlinha);
    
    in.close();
    
}