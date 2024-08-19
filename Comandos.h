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
	int ocorrencias = 0;
};



map<string, Comando> Comandos();
map<string, int> addRegistradores();