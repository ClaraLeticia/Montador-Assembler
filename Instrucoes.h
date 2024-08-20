#pragma once
#include <string>
#include "Comandos.h"
#include <map>

map<string, Comando> codificarInstrucao(string, string, map<string, int>);
void processarVariavel(string, int&);