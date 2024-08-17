#pragma once
#include <string>
#include <map>
using namespace std;

struct Comando {
	string nome;
	char tipo;
	int opcode;
	int rs;
	int rt;
	int rd;
	int constante; // Comandos tipo R = shamt;  Comandos tipo I = imediato; Comandos tipo J = endereço
	int func;
};



map<string, Comando> Comandos();
map<string, int> addRegistradores();