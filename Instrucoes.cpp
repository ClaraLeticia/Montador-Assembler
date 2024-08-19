#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <map>
#include <bitset>
#include <fstream>
#include "Comandos.h"
#include "BancoRegs.h"
#include "Codificador.h"
using namespace std;

void codificarInstrucao( string inputArquivo, string formato) {
   

    map<string, Comando> MapComandos = Comandos(); // Mapeando os comandos existentes
    map<string, int> mapRegis = addRegistradores(); // Mapeando os registradores
    int op = 0, rd = 0, rs = 0, rt = 0, sa = 0, funct = 0, constante = 0; // Inicializando 
     char pular = '\n';

    ifstream fin(inputArquivo, ios_base::in); // abrir arquivo assembly pra leitura
    string outputArquivo = inputArquivo.substr(0, inputArquivo.find_last_of('.')); // extrai o nome do arquivo sem a extens�o .asm

    if (formato == "-b") {
        outputArquivo += ".bin";
    }
    else if (formato == "-h") {
        outputArquivo += ".hex";
    }
    
    ofstream fout(outputArquivo, ios_base::binary); // abre arquivo bin para escrita

    string input;

    while (getline(fin, input)) { // � pra ler cada linha

        op = 0, rd = 0, rs = 0, rt = 0, sa = 0, funct = 0, constante = NULL;
        if (input.empty()) continue; // Ignora linhas em branco

        stringstream ss(input); // passa a linha de instru��o do arquivo como parametro
        string comando;
        string variavel;
        string comentario;

        vector<string> variaveis;
        vector<string> registradores;
        vector<int> registradoresInt;

        // Usar getline para separar a string com base no espa�amento buscando o comando
        getline(ss, comando, ' ');



        while (getline(ss, variavel, ',')) { // le cada palavra da linha, separadads por virgula

            

            if (!variavel.find('$')) { // Verifica se variavel � um registrador 
                registradores.push_back(variavel); // Caso seja vai para o vetor de registradores
            }
            else {
                constante = stoi(variavel); // STRING TO INTEGER ; valor immediate
            }

        }

        registradoresInt = regs(registradores, mapRegis); // Armazena apenas o valor DECIMAL do registrador; ex: $t0 = 8 e $8 = 8       

        

        for (auto i : MapComandos) {
            if (comando == i.first) {
                i.second.ocorrencias += 1;
                switch (i.second.tipo)
                {
                case 'R':
                    /*
                    Comandos do tipo R podem ter

                    � 2 registradores e 1 valor imediato (shamt) sll e srl
                    � Apenas 2 registradores (comandos 6 � 9)
                    � 3 registradores (10 � 18) n�o usando o shamt
                    � 1 registrador em rs (comando jr)
                    � 2 registrador em rd (comandos mfs)
                    */

                    if (registradoresInt.size() == 3) { // Verififica��o para comandos que utilizam 3 registradores (comandos 10 � 18)
                        rd = registradoresInt[0];
                        rs = registradoresInt[1];
                        rt = registradoresInt[2];

                        auto binaryInstruction = bitset<32>(codificador_typeR(i.second.opcode, rd, rs, rt, i.second.constante, i.second.func)).to_string(); // Codifica a instru��o
                        fout.write(binaryInstruction.c_str(), binaryInstruction.size());

                    }
                    else if (registradoresInt.size() == 2 && constante == NULL) { // Verificando para comandos que utilizam 2 registradores e nenhuma constante
                        rs = registradoresInt[0];
                        rt = registradoresInt[1];

                        auto binaryInstruction = bitset<32>(codificador_typeR(i.second.opcode, i.second.rd, rs, rt, i.second.constante, i.second.func)).to_string(); // Codifica a instru��o
                        fout.write(binaryInstruction.c_str(), binaryInstruction.size());
                    }
                    else if (constante != NULL) { // Verificando para comandos que utilizam 2 registradores e constante(shamt)
                        rd = registradoresInt[0];
                        rt = registradoresInt[1];

                        auto binaryInstruction = bitset<32>(codificador_typeR(i.second.opcode, rd, i.second.rs, rt, constante, i.second.func)).to_string(); // Codifica a instru��o
                        fout.write(binaryInstruction.c_str(), binaryInstruction.size());
                    }
                    else if (i.first == "jr") { // Verificando se � o comando jr
                        rs = registradoresInt[0];

                        auto binaryInstruction = bitset<32>(codificador_typeR(i.second.opcode, i.second.rd, rs, i.second.rt, i.second.constante, i.second.func)).to_string(); // Codifica a instru��o
                        fout.write(binaryInstruction.c_str(), binaryInstruction.size());
                    }
                    else if(i.first == "mfhi" || i.first == "mflo") { // Se n�o � o jr ent�o s� sobra os comandos mfhi e mflo
                        rd = registradoresInt[0];

                        auto binaryInstruction = bitset<32>(codificador_typeR(i.second.opcode, rd, i.second.rs, i.second.rt, i.second.constante, i.second.func)).to_string(); // Codifica a instru��o
                        fout.write(binaryInstruction.c_str(), binaryInstruction.size());
                    }

                    break;
                case 'I':
                    /*
                    Comandos do tipo I podem ter:
                    - 2 registradores e 1 constante
                        - beq e bne: regis[0] = rs, regis[1] = rt
                        - todos os outros: regis[1] = rs, regis[0] = rt
                    - 1 registrador e 1 constante (somente o 'lui')                 
                    */

                    if (registradoresInt.size() == 2) {
                        if (i.second.opcode == 4 or i.second.opcode == 5) { // restri��o para o 'beq' e 'bne'
                            rs = registradoresInt[0];
                            rt = registradoresInt[1];

                            auto binaryInstruction = bitset<32>(codificador_typeI(i.second.opcode, rs, rt, constante)).to_string(); // Codifica a instru��o
                            fout.write(binaryInstruction.c_str(), binaryInstruction.size());
                        }
                        else { // todos os outros comandos
                            rs = registradoresInt[1];
                            rt = registradoresInt[0];

                            auto binaryInstruction = bitset<32>(codificador_typeI(i.second.opcode, rs, rt, constante)).to_string(); // Codifica a instru��o
                            fout.write(binaryInstruction.c_str(), binaryInstruction.size());
                        }
                    }
                    else if (registradoresInt.size() == 1) { // comando 'lui'
                        rt = registradoresInt[0];

                        auto binaryInstruction = bitset<32>(codificador_typeI(i.second.opcode, i.second.rs, rt, constante)).to_string(); // Codifica a instru��o
                        fout.write(binaryInstruction.c_str(), binaryInstruction.size());
                    }
                    
                case 'J':
                {
                    /*
                    Comandos do tipo J podem ter:
                    - 1 constante (endere�o)
                    */

                    auto binaryInstruction = bitset<32>(codificador_typeJ(i.second.opcode, constante)).to_string(); // Codifica a instru��o
                    fout.write(binaryInstruction.c_str(), binaryInstruction.size());

                    break;

                }
                default:
                    break;
                }
                    
                break;
            }
           
        }

        fout.write(&pular, sizeof(pular));

    }
        fin.close();
        fout.close();

        for (auto i : MapComandos) {
            if (i.second.ocorrencias != 0) {
                cout << i.first << " - " << i.second.ocorrencias;
            }
        }
}
