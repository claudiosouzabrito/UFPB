#include <fstream>
#include <iostream>
#include <string>
using namespace std;
int main(){
    ofstream out;
    out.open("saida.tv");
    ifstream in;
    in.open("entrada");
    int l = 1;
    int antclock = 1;
    int clock = 0;
    int terclock;
    string linha;
    string opcode;
    string funct;
    int fim = 0;
    int estado = 0;
    int IorD = 0, AluSrcA = 0, IRWrite= 0, PCWrite= 0, RegDst= 0, MemtoReg= 0, RegWrite= 0, MemWrite= 0,
    Branch= 0;
    int AluSrcB[2] = {0,0}; int ALUOp[2]= {0,0}; int PCSrc[2]= {0,0};
    while(getline(in, linha)){
        opcode = linha.substr(2,6);
        funct = linha.substr(9,6);
        cout << "linha = " << l << ", " /<< linha[0] << ", "/;
        while(1){
            if(linha[0] == '1'){
                cout << "reset = 1, estado = 0";
                estado = 0;
                IorD = 0;
                AluSrcA = 0;
                AluSrcB[0] = 0; AluSrcB[1] = 1;
                ALUOp[0] = 0; ALUOp[1] = 0;
                PCSrc[0] = 0; PCSrc[1] = 0;
                IRWrite = 1;
                PCWrite = 1;
                out << "1_" << clock << "" << opcode << "" << funct << "_" <<
                IorD << "" << AluSrcA << "" << IRWrite << "" << PCWrite << "" << RegDst <<
                "" << MemtoReg << "" << RegWrite << "" << MemWrite << "" << Branch << "_" << 
                AluSrcB[0] << AluSrcB[1] << "" << ALUOp[0] << ALUOp[1] << "" << PCSrc[0] << PCSrc[1]
                << "_" << estado << endl;
                cout << endl;
                IRWrite = 0;
                PCWrite = 0;
                terclock = antclock;
                antclock = clock;
                clock = terclock;
                break;
            }
            if(clock){
                cout << "subida de clock, estado anterior " << estado << ", ";
                switch (estado){
                    case 0:
                        IorD = 0;
                        AluSrcA = 0;
                        AluSrcB[0] = 0; AluSrcB[1] = 1;
                        ALUOp[0] = 0; ALUOp[1] = 0;
                        PCSrc[0] = 0; PCSrc[1] = 0;
                        IRWrite = 1;
                        PCWrite = 1;
                        cout << "estado novo: " << ++estado;
                        break;
                    case 1:
                        AluSrcA = 0;
                        AluSrcB[0] = 1; AluSrcB[1] = 1;
                        ALUOp[0] = 0; ALUOp[1] = 0;
                        if(!opcode.compare("100011") || !opcode.compare("101011")){
                            cout << "load/store detectado, indo para estado 2";
                            estado = 2;
                        }
                        else if(!opcode.compare("000000")){
                            cout << "instrucao tipo R detectado";
                            estado = 6;
                        }
                        else if(!opcode.compare("000100") || !opcode.compare("000101")){
                            cout << "instrucao tipo branch detectado";
                            estado = 8;
                        }
                        else if(!opcode.compare("001000")){
                            cout << "instrucao ADDI detectada";
                            estado = 9;
                        }
                        else if(!opcode.compare("000010")){
                            cout << "instrucao jump detectada";
                            estado = 11;
                        }
                        break;
                    case 2:
                        AluSrcA = 1;
                        AluSrcB[0] = 1; AluSrcB[1] = 0;
                        ALUOp[0] = 0; ALUOp[1] = 0;
                        if(!opcode.compare("100011")){
                            cout << ", lw detectado, indo para estado 3";
                            estado = 3;
                        //    out << "0_" << clock << "" << opcode << "" << funct << "_3" << endl;
                        }
                        else if(!opcode.compare("101011")){
                            cout << ", sw detectado, indo para estado 5";
                            estado = 5;
                        //    out << "0_" << clock << "" << opcode << "" << funct << "_5" << endl;
                        }
                        break;
                    case 3:
                        IorD = 1;
                        cout << "estado novo: " << ++estado;
                        break;
                    case 4:
                        RegDst = 0;
                        MemtoReg = 1;
                        RegWrite = 1;
                        cout << "fim da linha, voltando para o estado 0";
                        estado = 0;
                    //    out << "0_" << clock << "" << opcode << "" << funct << "_0" << endl;
                        fim = 1;
                        break;
                    case 5:
                        IorD = 1;
                        MemWrite = 1;
                        cout << "fim da linha, voltando para o estado 0";
                        estado = 0;
                    //    out << "0_" << clock << "" << opcode << "" << funct << "_0" << endl;
                        fim = 1;
                        break;
                    case 6:
                        AluSrcA = 1;
                        AluSrcB[0] = 0; AluSrcB[1] = 0;
                        ALUOp[0] = 1; ALUOp[1] = 0;
                        if(!funct.compare("100000")){
                            cout << ", ADD detectado, indo para o estado 61";
                            estado = 61;
                        }
                        else if(!funct.compare("100010")){
                            cout << ", SUB detectado, indo para o estado 62";
                            estado = 62;
                        }
                        else if(!funct.compare("100100")){
                            cout << ", AND detectado, indo para o estado 63";
                            estado = 63;
                        }
                        else if(!funct.compare("100101")){
                            cout << ", OR detectado, indo para o estado 64";
                            estado = 64;
                        }
                        else if(!funct.compare("100111")){
                            cout << ", NOR detectado, indo para o estado 65";
                            estado = 65;
                        }
                        else if(!funct.compare("100110")){
                            cout << ", XOR detectado, indo para o estado 66";
                            estado = 66;
                        }
                        break;
                    case 61:
                        estado = 7;
                        cout << "estado novo: " << estado;
                        break;
                    case 62:
                        estado = 7;
                        cout << "estado novo: " << estado;
                        break;
                    case 63:
                        estado = 7;
                        cout << "estado novo: " << estado;
                        break;
                    case 64:
                        estado = 7;
                        cout << "estado novo: " << estado;
                        break;
                    case 65:
                        estado = 7;
                        cout << "estado novo: " << estado;
                        break;
                    case 66:
                        estado = 7;
                        cout << "estado novo: " << estado;
                        break;
                    case 7:
                        RegDst = 1;
                        MemtoReg = 0;
                        RegWrite = 1;
                        cout << "fim da linha, voltando para o estado 0";
                        estado = 0;
                    //    out << "0_" << clock << "" << opcode << "" << funct << "_0" << endl;
                        fim = 1;
                        break;
                    case 8:
                        AluSrcA = 1;
                        AluSrcB[0] = 0; AluSrcB[1] = 0;
                        ALUOp[0] = 0; ALUOp[1] = 1;
                        PCSrc[0] = 0; PCSrc[1] = 1;
                        Branch = 1;
                        cout << "fim da linha, voltando para o estado 0";
                        estado = 0;
                    //    out << "0_" << clock << "" << opcode << "" << funct << "_0" << endl;
                        fim = 1;
                        break;
                    case 9:
                        AluSrcA = 1;
                        AluSrcB[0] = 1; AluSrcB[1] = 0;
                        ALUOp[0] = 0; ALUOp[1] = 0;
                        cout << "estado novo: " << ++estado;
                        break;
                    case 10:
                        RegDst = 0;
                        MemtoReg = 0;
                        RegWrite = 1;
                        cout << "fim da linha, voltando para o estado 0";
                        estado = 0;
                    //    out << "0_" << clock << "" << opcode << "" << funct << "_0" << endl;
                        fim = 1;
                        break;
                    case 11:
                        PCSrc[0] = 1; PCSrc[1] = 0;
                        PCWrite = 1;
                        cout << "fim da linha, voltando para o estado 0";
                        estado = 0;
                    //    out << "0_" << clock << "" << opcode << "" << funct << "_0" << endl;
                        fim = 1;
                        break;
                    default:
                        cout << "fim da linha, voltando para o estado 0";
                        estado = 0;
                    //    out << "0_" << clock << "" << opcode << "" << funct << "_0" << endl;
                        fim = 1;
                        break;
                }
            }  
            else cout << "descida de clock: ";
            out << "1_" << clock << "" << opcode << "" << funct << "_" <<
                IorD << "" << AluSrcA << "" << IRWrite << "" << PCWrite << "" << RegDst <<
                "" << MemtoReg << "" << RegWrite << "" << MemWrite << "" << Branch << "_" << 
                AluSrcB[0] << AluSrcB[1] << "" << ALUOp[0] << ALUOp[1] << "" << PCSrc[0] << PCSrc[1]
                << "_" << estado << endl;
            cout << endl;
            IRWrite = 0;
            PCWrite = 0;
            RegWrite = 0;
            MemWrite = 0;
            Branch = 0;
            terclock = antclock;
            antclock = clock;
            clock = terclock;
            if(fim){
                fim = 0;
                break;
            }  
        }
        l++;
    }
    in.close();
    out.close();
}