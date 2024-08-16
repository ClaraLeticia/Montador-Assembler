#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <map>
#include "Comandos.h"
#include <bitset>

using namespace std;

long int regis_to_bin(int op, int rd, int rs, int rt, int sa, int funct, int imediato) {
	long int cod;
	int op_bin = bitset<6>(op);
	int rs_bin = bitset<5>(rs);
	int rt_bin = bitset<5>(rt);
	int rd_bin = bitset<5>(rd);
	int sa_bin = bitset<5>(imediato);
	int funct_bin = bitset<6>(funct);

	return op_bin + rs_bin + rt_bin + rd_bin + sa_bin + funct_bin;
}


