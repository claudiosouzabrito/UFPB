#include <iostream>
#include <fstream> 
#include <bitset>
#include <cstdio>
int main() {
    std::ofstream saida("saida.tv", std::ios::out);
    long long i = 0;
    saida << std::bitset<26>(i).to_string() << "_" << (std::bitset<28>(i) << 2).to_string() << std::endl;
    i = INT64_MAX;
    saida << std::bitset<26>(i).to_string() << "_" << (std::bitset<28>(i) << 2).to_string() << std::endl;


}