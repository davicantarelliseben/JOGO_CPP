#include <iostream>
#include <fstream>
#include <string>


int main(){
    std::ifstream arquivo("mapahash");

    if(!arquivo.is_open()){
        std::cerr << "Erro ao abrir o arquivo" << "\n";
        return 1;
    }

    std::string linha;

    while (std::getline(arquivo,linha)){
        std::cout << linha << "\n";
    }

    arquivo.close();
    

}