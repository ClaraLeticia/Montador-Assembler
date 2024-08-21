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
#include "Instrucoes.h"
#include "cpi.h"
#include "Labels.h"
#include <map>
using namespace std;

int main(int argc, char* argv[]) {

	string inputArquivo = argv[1]; // arquivo assembly
	string formato = argv[2]; // '-b' ou '-h'
	
	map<string, int> mapLabels = identificandoLabels(inputArquivo);

	

	map<string, Comando> qtdInstrucoes = codificarInstrucao(inputArquivo, formato, mapLabels);
	//calcularCPI(qtdInstrucoes);



	
	
}