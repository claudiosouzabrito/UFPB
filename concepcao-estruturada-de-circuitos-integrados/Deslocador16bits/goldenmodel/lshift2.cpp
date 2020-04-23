#include <iostream>
#include <fstream> 
#include <bitset>
#include <cstdio>
int main() {
    std::ofstream saida("saida.tv", std::ios::out);
    long long i = 0;
    saida << std::bitset<16>(i).to_string() << "_" << (std::bitset<18>(i) << 2).to_string() << std::endl;
    i = INT64_MAX;
    saida << std::bitset<16>(i).to_string() << "_" << (std::bitset<18>(i) << 2).to_string() << std::endl;


}