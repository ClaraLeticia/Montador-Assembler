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
    map<string, Comando> MapComandos = Comandos(); // Mapeando os comandos existentes
    map<string, int> mapRegis = addRegistradores(); // Mapeando os registradores
    int op = 0, rd = 0, rs = 0, rt = 0, sa = 0, funct = 0, constante = 0; // Inicializando 
     char pular = '\n';


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
        op = 0, rd = 0, rs = 0, rt = 0, sa = 0, funct = 0, constante = NULL;
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
                constante = stoi(variavel); // STRING TO INTEGER ; valor immediate
            }

        }

        registradoresInt = regs(registradores, mapRegis); // Armazena apenas o valor DECIMAL do registrador; ex: $t0 = 8 e $8 = 8

        

        for (auto i : MapComandos) {
            if (comando == i.first) {
                if (i.second.tipo == 'R') {
                    /*
                        Comandos do tipo R podem ter

                        • 2 registradores e 1 valor imediato (shamt) sll e srl
                        • Apenas 2 registradores (comandos 6 à 9)
                        • 3 registradores (10 à 18) não usando o shamt
                        • 1 registrador em rs (comando jr)
                        • 2 registrador em rd (comandos mfs)
                        */



                    if (registradoresInt.size() == 3) { // Verifificação para comandos que utilizam 3 registradores (comandos 10 à 18)
                        rd = registradoresInt[0];
                        rs = registradoresInt[1];
                        rt = registradoresInt[2];

                        auto binaryInstruction = bitset<32>(codificador_typeR(i.second.opcode, rd, rs, rt, i.second.constante, i.second.func)).to_string(); // Codifica a instruçãp
                        fout.write(binaryInstruction.c_str(), binaryInstruction.size());

                    }
                    else if(registradoresInt.size() == 2 && constante == NULL) { // Verificando para comandos que utilizam 2 registradores e nenhuma constante
                        rs = registradoresInt[0];
                        rt = registradoresInt[1];
                       
                        auto binaryInstruction = bitset<32>(codificador_typeR(i.second.opcode, i.second.rd, rs, rt, i.second.constante, i.second.func)).to_string(); // Codifica a instruçãp
                        fout.write(binaryInstruction.c_str(), binaryInstruction.size());
                    }
                    else if (constante != NULL) { // Verificando para comandos que utilizam 2 registradores e constante(shamt)
                        rd = registradoresInt[0];
                        rt = registradoresInt[1];
                      

                        auto binaryInstruction = bitset<32>(codificador_typeR(i.second.opcode, rd, i.second.rs, rt, constante, i.second.func)).to_string(); // Codifica a instruçãp
                        fout.write(binaryInstruction.c_str(), binaryInstruction.size());
                    }
                    else if(i.first == "jr") { // Verificando se é o comando jr
                        rs = registradoresInt[0];

                        auto binaryInstruction = bitset<32>(codificador_typeR(i.second.opcode, i.second.rd, rs, i.second.rt, i.second.constante, i.second.func)).to_string(); // Codifica a instruçãp
                        fout.write(binaryInstruction.c_str(), binaryInstruction.size());
                    }
                    else { // Se não é o jr então só sobra os comandos mfhi e mflo
                        rd = registradoresInt[0];

                        auto binaryInstruction = bitset<32>(codificador_typeR(i.second.opcode, rd, i.second.rs, i.second.rt, i.second.constante, i.second.func)).to_string(); // Codifica a instruçãp
                        fout.write(binaryInstruction.c_str(), binaryInstruction.size());
                    }


                    break;
                }
            }
        }


        fout.write(&pular, sizeof(pular));

    }
        fin.close();
        fout.close();

        return 0;
}
