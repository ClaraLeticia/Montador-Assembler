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
    int op = 0, rd = 0, rs = 0, rt = 0, sa = 0, funct = 0, addrees = 0, imediato; // Inicializando 
    auto binaryInstruction;

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
        op = 0, rd = 0, rs = 0, rt = 0, sa = 0, funct = 0, addrees = 0, imediato = 0; 
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


        // Usar getline para separar a string com base no espaçamento buscando o comando
        getline(ss, comando, ' '); 

        while (getline(ss, variavel, ',')) { // le cada palavra da linha, separadads por virgula
            if (!variavel.find('$')) { // Verifica se variavel é um registrador 
                registradores.push_back(variavel); // Caso seja vai para o vetor de registradores
            }
            else {
                imediato = stoi(variavel); // STRING TO INTEGER ; valor immediate
            }

        }

        cout << registradores << endl << imediato << endl;

        registradoresInt = regs(registradores, mapRegis); // Armazena apenas o valor DECIMAL do registrador; ex: $t0 = 8 e $8 = 8

        /*

        for (auto i : MapComandos) {
            if (comando == i.first) {
                if (i.second.tipo == 'R') {
                    
                        Comandos do tipo R podem ter

                    	• 2 registradores e 1 valor imediato (shamt) sll e srl
	                    • Apenas 2 registradores (comandos 6 à 9)
	                    • 3 registradores (10 à 18)
	                    • 1 registrador em rs (comando jr)
	                    • 2 registrador em rd (comandos mfs)

                    */
        /*

                    if (registradoresInt.size == 3) {
                        rd = registradoresInt[0];
                        rs = registradoresInt[1];
                        rt = registradoresInt[2];

                        binaryInstruction = bitset<32>(codificador_typeR(op, rd, rs, rt, sa, i.second.func)).to_string(); // Codifica a instruçãp
                        fout.write(binaryInstruction.c_str(), binaryInstruction.size());
              
                    }

                // PARA O TIPO I
                else if (i.second.tipo == 'I') {
                    auto binaryInstruction = bitset<32>(codificador_typeI(op, rs, rt, sa)).to_string();
                    fout.write(binaryInstruction.c_str(), binaryInstruction.size());
                }
            }
        }
    }
    8*/
    
    //cout << bitset<6>(op) << bitset<5>(rs) << bitset<5>(rt) << bitset<5>(rd) << bitset<5>(sa) << bitset<6>(funct); // tipo R

    fin.close();
    fout.close();

    return 0;
}
