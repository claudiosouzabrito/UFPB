

#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include <stdio.h>
#include <stdlib.h> 
#include<vector>
#include<math.h>
using namespace std;

long int DistanciaEuclidiana(long int w1, long int w2, long int z1, long int z2) {

    long int dist=0;

    
    return dist;
  }


int main(){
  string text, aux;
  int count_inst=0;
  //vector <int> aux2;
  int aux2[1000], l;
  vector <string> text2;
  int i, k, p, tam=15, j, cont;
  long int instancia[1000];
  long int x1[1000], x2[1000], distancia;
  long int matriz[1000][1000];
  long int Total, mult;
  
  ifstream arq;
  arq.open("tsp1.txt", ios::in);
  
  if (arq.is_open() && arq.good()){
    getline(arq, text);
    getline(arq, text);
    cout<<"Arquivo ok "<<text<<endl;
    i=0;
    while(arq){
      getline(arq, text);
      //text = "33 57483.90 634688.55";
      //cout<<"le linha "<<i<<endl;
      text2.push_back(text);
      //cout<<text2[i]<<endl;
      aux = text2[i];//pega linha
        for(j=0, cont =0; j< aux.length(); j++){ 
          if((int)aux[j]>=48  && (int)aux[j]<=57){//procura numero na linha
            aux2[cont] =aux[j]-48;
            //cout<<aux2[cont]<<" ";
            cont++;
          }else if((int)aux[j]== 32){ //checa o espaço
            if(cont >  0){
              for(Total=0, k=cont, p=0; k>0;p++, k--){
                for(l=1, mult=1; l<k; l++){
                            mult*=10;
                        }//cout<<mult<<" ";
                        Total+=(aux2[p])*(mult);
              }//cout<<Total<<endl;
              instancia[count_inst] = Total;
              count_inst++;
            }cont=0;
          }else if((int)aux[j]== 46){ //checa o ponto
            if(cont >  0){
              for(Total=0, k=cont, p=0; k>0;p++, k--){
                for(l=1, mult=1; l<k; l++){
                            mult*=10;
                        }//cout<<mult<<" ";
                        Total+=(aux2[p])*(mult);
                        //cout<<Total<<" + ";
              }//cout<<Total<<endl;
              instancia[count_inst] = Total;
              count_inst++;
            }cont=0;
            j+=2;
          }
        }//cout<<count_inst<<endl;
      i++;
    }
  }else
    cout<<"ERRO"<<endl;

    cout<<endl<<count_inst<<endl;

    for(i=0, cont=0; i<count_inst; i++){

      //cout<<instancia[i]<<" ";
      if(i==0 || i%3==0){
        //col[]=instancia[i];
      }else if(i==1 || (i-1)%3==0){
        x1[cont] = instancia[i];
      }else{
        x2[cont] = instancia[i];
        cont++;
      }
    }


    cout<<endl<<cont<<endl<<tam<<endl;


  for( i=0; i<tam; i++){
    cout<<"linha - "<<i<<"  ";
      for( j = 0; j<tam; j++){
        cout<<x1[i]<<" "<<x1[j]<<" "<<x2[i]<<" "<<x2[j]<<" ";
          distancia = sqrt(((x1[i] - x1[j])^2) + ((x2[i] - x2[j])^2));
          cout << "Distancia Euclidiana: " << ((x2[i] - x2[j])^2)<< endl;
          matriz[i][j] = distancia;
          //cout<<matriz[i][j]<<" ";
      }cout<<endl;

  }
  arq.close();
  return 0;
}

