#include <fstream>
#include <iostream>
#include "cpi.h"
using namespace std;

void calcularCPI() {
	fstream fout;

	fout.open("instrucao.csv");

    if (!fout.is_open()) {
        cerr << "Erro ao abrir o arquivo de sa�da teste.bin!" << endl;
    }
    cout << "Arquivo de sa�da aberto com sucesso!" << endl;
}