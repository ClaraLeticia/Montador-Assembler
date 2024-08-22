#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <map>
#include <bitset>
#include "Comandos.h"
#include "Codificador.h"

using namespace std;

long int codificador_typeR(int op, int rd, int rs, int rt, int sa, int funct) {
    long int cod = (op << 26) | (rs << 21) | (rt << 16) | (rd << 11) | (sa << 6) | funct;

    return cod;
}

long int codificador_typeI(int op, int rs, int rt, int immediate) {
    long int cod = (op << 26) | (rs << 21) | (rt << 16) | immediate;

    return cod;
}

long int codificador_typeJ(int op, int address) {
    long int cod = (op << 26) | address;

    return cod;
}

