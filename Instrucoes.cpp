#include <iostream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <string>
#include <map>
#include <bitset>
#include <fstream>
#include "Comandos.h"
#include "BancoRegs.h"
#include "Codificador.h"
using namespace std;

void processarVariavel(string variavel, int& constante) {
    bool isNumber = true;
    for (char c : variavel) {
        if (!isdigit(c)) {
            isNumber = false;
            break;
        }
    }

    if (isNumber) {
        constante = stoi(variavel);
    }
}


map<string, Comando> codificarInstrucao( string inputArquivo, string formato, map<string, int> mapLabels) {
    const int endereco_inicial = 0x00400000;
    int endereco = endereco_inicial;
    int pc = 2;
    map<string, Comando> MapComandos = Comandos(); // Mapeando os comandos existentes
    map<string, int> mapRegis = addRegistradores(); // Mapeando os registradores
    int op = 0, rd = 0, rs = 0, rt = 0, sa = 0, funct = 0, constante = 0; // Inicializando 
    char pular = '\n';
    auto codificacao = bitset<32>(0);

    ifstream fin(inputArquivo, ios_base::in); // abrir arquivo assembly pra leitura
    string outputArquivo = inputArquivo.substr(0, inputArquivo.find_last_of('.')); // extrai o nome do arquivo sem a extensão .asm

    if (formato == "-b") {
        outputArquivo += ".bin";
    }
    else if (formato == "-h") {
        outputArquivo += ".hex";
    }
    
    ofstream fout(outputArquivo, ios_base::binary); // abre arquivo bin para escrita

    if (formato == "-h") {
        fout << "v2.0 raw\n";
    }

    string input;

    while (getline(fin, input)) { // é pra ler cada linha  
        size_t comentario = input.find('#');

        if (comentario != string::npos) {
            input = input.substr(0, comentario - 1); // input vira uma substring de input que vai da posição 0 até a posição que se encontra o comentário
        }
        
        bool label = false;
        size_t findLabel = input.find(':'); // procura a ocorrência de label na linha

        if (findLabel != string::npos) {
            label = true;
        }

        op = 0, rd = 0, rs = 0, rt = 0, sa = 0, funct = 0, constante = NULL;
        if (input.empty()) continue; // Ignora linhas em branco
        stringstream ss(input); // passa a linha de instrução do arquivo como parametro
        string comando;
        string variavel;

        vector<string> variaveis;
        vector<string> registradores;
        vector<int> registradoresInt;

        // Usar getline para separar a string com base no espaçamento buscando o comando
        getline(ss, comando, ' ');

        while (getline(ss, variavel, ',')) { // le cada palavra da linha, separadads por virgula

            size_t abertura_lw_sw = variavel.find("(");
            size_t fechadura_lw_sw = variavel.find(")");

            if (abertura_lw_sw != string::npos) {
                constante = stoi(variavel.substr(0, abertura_lw_sw)); 
                registradores.push_back(variavel.substr(abertura_lw_sw + 1, fechadura_lw_sw - abertura_lw_sw - 1));
            }
            else if (!variavel.find('$')) { // Verifica se variavel é um registrador 
                registradores.push_back(variavel); // Caso seja vai para o vetor de registradores
            }
            else {
                
                processarVariavel(variavel, constante);
               
            }

        }

        registradoresInt = regs(registradores, mapRegis); // Armazena apenas o valor DECIMAL do registrador; ex: $t0 = 8 e $8 = 8        

        map<string, Comando> ::iterator it;
        for (it = MapComandos.begin(); it != MapComandos.end(); it++) {
            if (comando == (*it).first) {
                
                (*it).second.ocorrencias += 1;
                switch ((*it).second.tipo)
                {
                case 'R':
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
                        

                        codificacao = codificador_typeR((*it).second.opcode, rd, rs, rt, (*it).second.constante, (*it).second.func); // Codifica a instrução                    
                    }
                    else if (registradoresInt.size() == 2 && constante == NULL) { // Verificando para comandos que utilizam 2 registradores e nenhuma constante
                        rs = registradoresInt[0];
                        rt = registradoresInt[1];

                        codificacao = codificador_typeR((*it).second.opcode, (*it).second.rd, rs, rt, (*it).second.constante, (*it).second.func); // Codifica a instrução                     
                    }
                    else if (constante != NULL) { // Verificando para comandos que utilizam 2 registradores e constante(shamt)
                        rd = registradoresInt[0];
                        rt = registradoresInt[1];

                        codificacao = codificador_typeR((*it).second.opcode, rd, (*it).second.rs, rt, constante, (*it).second.func); // Codifica a instrução                    
                    }
                    else if ((*it).first == "jr") { // Verificando se é o comando jr
                        rs = registradoresInt[0];

                        codificacao = codificador_typeR((*it).second.opcode, (*it).second.rd, rs, (*it).second.rt, (*it).second.constante, (*it).second.func); // Codifica a instrução
                    }
                    else if((*it).first == "mfhi" || (*it).first == "mflo") { // Se não é o jr então só sobra os comandos mfhi e mflo
                        rd = registradoresInt[0];

                        codificacao = codificador_typeR((*it).second.opcode, rd, (*it).second.rs, (*it).second.rt, (*it).second.constante, (*it).second.func); // Codifica a instrução
                    }

                    if (formato == "-b") {
                        fout.write(bitset<32>(codificacao).to_string().c_str(), codificacao.size());
                    }
                    else if (formato == "-h") {
                        fout << hex << setw(8) << setfill('0') << stoi(codificacao.to_string(), nullptr, 2);
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
                        if ((*it).second.opcode == 4 or (*it).second.opcode == 5) { // restrição para o 'beq' e 'bne'
                            for (auto j : mapLabels) {
                                if (variavel == j.first) {
                                    
                                    constante =  j.second - pc;
                                }
                            }
                            
                            rs = registradoresInt[0];
                            rt = registradoresInt[1];
                            bitset<16> bits(constante);
                            constante = static_cast<int>(bits.to_ulong()); // Transformando um numero binário para inteiro

                            codificacao = codificador_typeI((*it).second.opcode, rs, rt, constante); // Codifica a instrução  
                           
                        }
                        else { // todos os outros comandos
                            rs = registradoresInt[1];
                            rt = registradoresInt[0];

                            codificacao = codificador_typeI((*it).second.opcode, rs, rt, constante); // Codifica a instrução                            
                            
                        }

                    }
                    else if (registradoresInt.size() == 1) { // comando 'lui'
                        rt = registradoresInt[0];

                        codificacao = codificador_typeI((*it).second.opcode, (*it).second.rs, rt, constante); // Codifica a instrução
                    }

                    if (formato == "-b") {
                        fout.write(bitset<32>(codificacao).to_string().c_str(), codificacao.size());
                    }
                    else if (formato == "-h") {
                        fout << hex << setw(8) << setfill('0') << static_cast<int>(codificacao.to_ulong());;
                    }

                    break;

                case 'J':
                {
                    /*
                    Comandos do tipo J podem ter:
                    - 1 constante (endereço)
                    */

                    for (auto i : mapLabels) {
                        if (i.first == variavel) {
                            
                            constante = (i.second - 1) * 4 + endereco_inicial;
                            break;
                        }
                    }
                    
                    constante /= 4;

                    codificacao = codificador_typeJ((*it).second.opcode, constante); // Codifica a instrução
                    
                    if (formato == "-b") {
                        fout.write(bitset<32>(codificacao).to_string().c_str(), codificacao.size());
                    }
                    else if (formato == "-h"){
                     
                        fout << hex << setw(8) << setfill('0') << stoi(codificacao.to_string(), nullptr, 2);
                    }

                    break;

                }
                default:
                    break;
                }
                
                    
                break;
            }
            
        }

        

        if (!label) {
            pc++;
            fout.write(&pular, sizeof(pular)); // se não for uma linha vazia com label
            endereco += 4;   
        }
    }
        fin.close();
        fout.close();

        return MapComandos;
}
