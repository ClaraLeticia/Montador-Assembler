#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <map>
#include "Comandos.h"
#include "BancoRegs.h"
#include  <bitset>
using namespace std;


int main() {
    map<string, RComando> MapComandos = addRComandos(); // Mapeando os comandos existentes
    map<string, int> mapRegis = addRegistradores(); // Mapeando os registradores

    int op = 0, rd = 0, rs = 0, rt = 0, sa = 0, funct = 0;

    string input = "sll $8,$9,3";
    vector<string> variaveis;
    vector<string> registradores;
    vector<int> registradoresInt;
    string variavel;
    int imediato = 0;

    stringstream ss(input);
    string comando;

    // Usar std::getline para separar a string com base na vírgula
    getline(ss, comando, ' ');

   
    while (getline(ss, variavel, ',')) {

        if (!variavel.find('$')) { // Verifica se variavel é um registrador 
            registradores.push_back(variavel);
        }
        else {
            imediato = stoi(variavel); // STRING TO INTEGER
        }
       
        
    }

    registradoresInt = regs(registradores, mapRegis);
    rd = registradoresInt[0];
    rs = registradoresInt[1];
    


        for (auto i : MapComandos) {
            if (comando == i.first) {
                if (i.second.tipo == 'R') {
                    regis_to_bin(i, registradoresInt, imediato);
               }
            }
        } 

    
    cout << bitset<6>(op) << bitset<5>(rs) << bitset<5>(rt) << bitset<5>(rd) << bitset<5>(imediato) << bitset<6>(funct);
   

    

    
  


    return 0;
}
