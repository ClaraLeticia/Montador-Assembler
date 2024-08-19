#include <fstream>
#include <iostream>
#include "cpi.h"
using namespace std;

void calcularCPI() {
	fstream fout;

	fout.open("instrucao.csv");

    if (!fout.is_open()) {
        cerr << "Erro ao abrir o arquivo de saída teste.bin!" << endl;
    }
    cout << "Arquivo de saída aberto com sucesso!" << endl;
}