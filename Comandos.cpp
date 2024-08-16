#include <iostream>
#include <string>
#include <map>
#include "Comandos.h"
#include <bitset>
using namespace std;

map<string, RComando> addRComandos() {
	RComando sll{ "sll", 'R', 0, 0, 0, 0, 0, 0 };
	RComando srl{ "srl", 'R', 0, 0, 0, 0, 0, 2 };
	RComando add{ "add", 'R', 0, 0, 0, 0, 0, 32 };
	map<string, RComando> mapComandos = { {"sll", sll}, {"srl", srl}, {"add", add}};

	return mapComandos;
}

map<string, int> addRegistradores() {

	map<string, int> mapRegs = { { "$8", 8 }, { "$9", 9 } };


	return mapRegs;
}
