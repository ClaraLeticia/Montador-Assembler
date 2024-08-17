#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <map>
#include <bitset>
#include <fstream>
#include "Comandos.h"
#include "BancoRegs.h"
#include "CodificadorR.h"
using namespace std;


int main() {
    map<string, RComando> MapComandos = addRComandos(); // Mapeando os comandos existentes
    map<string, int> mapRegis = addRegistradores(); // Mapeando os registradores

    ifstream fin("teste.asm", ios_base::in); // abrir arquivo assembly pra leitura
    /*
    if (!fin.is_open()) {
        cerr << "Erro ao abrir o arquivo de entrada teste.asm!" << endl;
        return 1;
    }
    cout << "Arquivo de entrada aberto com sucesso!" << endl;
    */

    ofstream fout("teste.bin", ios_base::binary); // abre arquivo bin para escrita
    /*
    if (!fout.is_open()) {
        cerr << "Erro ao abrir o arquivo de saída teste.bin!" << endl;
        return 1;
    }
    cout << "Arquivo de saída aberto com sucesso!" << endl;
    */

    string input;

    while (getline(fin, input)) { // é pra ler cada linha
        if (input.empty()) continue; // Ignora linhas em branco

        //string input = "sll $8,$9,3";
        //string input = "add $8,$17,$18";
        //string input = "beq $8,$9,3";

        stringstream ss(input); // passa a linha de instrução do arquivo como parametro
        string comando;
        string variavel;

        vector<string> variaveis;
        vector<string> registradores;
        vector<int> registradoresInt;

        int op = 0, rd = 0, rs = 0, rt = 0, sa = 0, funct = 0;

        // Usar std::getline para separar a string com base no espaçamento
        getline(ss, comando, ' ');

        int qtdCifrao = 0;

        while (getline(ss, variavel, ',')) { // le cada palavra da linha, separadads por virgula
            if (!variavel.find('$')) { // Verifica se variavel é um registrador 
                registradores.push_back(variavel);
                qtdCifrao++;
            }
            else {
                sa = stoi(variavel); // STRING TO INTEGER ; valor immediate
            }

        }

        registradoresInt = regs(registradores, mapRegis);

        // teste para tipo R
        if (qtdCifrao > 2) {
            rd = registradoresInt[0];
            rs = registradoresInt[1];
            rt = registradoresInt[2];
        }
        else {
            rd = registradoresInt[0];
            rs = registradoresInt[1];
        }

        // teste para tipo I
        // rs = registradoresInt[0];
        // rt = registradoresInt[1];

        for (auto i : MapComandos) {
            if (comando == i.first) {
                if (i.second.tipo == 'R') {
                    auto binaryInstruction = bitset<32>(codificador_typeR(op, rd, rs, rt, sa, i.second.func)).to_string();
                    fout.write(binaryInstruction.c_str(), binaryInstruction.size());
                }
                else if (i.second.tipo == 'I') {
                    auto binaryInstruction = bitset<32>(codificador_typeI(op, rs, rt, sa)).to_string();
                    fout.write(binaryInstruction.c_str(), binaryInstruction.size());
                }
            }
        }
    }
    
    //cout << bitset<6>(op) << bitset<5>(rs) << bitset<5>(rt) << bitset<5>(rd) << bitset<5>(sa) << bitset<6>(funct); // tipo R

    fin.close();
    fout.close();

    return 0;
}
