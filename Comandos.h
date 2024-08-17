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

struct IComando {
	string nome;
	char tipo;
	int opcode;
	int rs;
	int rt;
	int immediate;
};

map<string, RComando> addRComandos();
map<string, IComando> addIComandos();
map<string, int> addRegistradores();