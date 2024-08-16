#pragma once
#include <string>
#include <map>
using namespace std;

struct RComando {
	string nome;
	char tipo;
	int opcode;
	int rs;
	int rt;
	int rd;
	int sa;
	int func;
};

map<string, RComando> addRComandos();
map<string, int> addRegistradores();