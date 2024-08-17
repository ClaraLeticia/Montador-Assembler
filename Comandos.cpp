#include <iostream>
#include <string>
#include <map>
#include "Comandos.h"
#include <bitset>
using namespace std;

map<string, RComando> addRComandos() {

    RComando sll{ "sll", 'R', 0, 0, 0, 0, 0, 0 };
    RComando srl{ "srl", 'R', 0, 0, 0, 0, 0, 2 };
    RComando jr{ "jr", 'R', 0, 0, 0, 0, 0, 8 };
    RComando mfhi{ "mfhi", 'R', 0, 0, 0, 0, 0, 16 };
    RComando mflo{ "mflo", 'R', 0, 0, 0, 0, 0, 18 };
    RComando mult{ "mult", 'R', 0, 0, 0, 0, 0, 24 };
    RComando multu{ "multu",'R', 0, 0, 0, 0, 0, 25 };
    RComando div{ "div", 'R', 0, 0, 0, 0, 0, 26 };
    RComando divu{ "divu", 'R', 0, 0, 0, 0, 0, 27 };
    RComando add{ "add", 'R', 0, 0, 0, 0, 0, 32 };
    RComando addu{ "addu", 'R', 0, 0, 0, 0, 0, 33 };
    RComando sub{ "sub", 'R', 0, 0, 0, 0, 0, 34 };
    RComando subu{ "subu", 'R', 0, 0, 0, 0, 0, 35 };
    RComando andd{ "and", 'R', 0, 0, 0, 0, 0, 36 }; // ja tem and no c++
    RComando orr{ "or", 'R', 0, 0, 0, 0, 0, 37 }; // ja tem or
    RComando slt{ "slt", 'R', 0, 0, 0, 0, 0, 42 };
    RComando sltu{ "sltu", 'R', 0, 0, 0, 0, 0, 43 };

	map<string, RComando> mapComandos = { 
        {"sll",   sll},
        {"srl",   srl},
        {"jr",    jr},
        {"mfhi",  mfhi},
        {"mflo",  mflo},
        {"mult",  mult},
        {"multu", multu},
        {"div",   div},
        {"divu",  divu},
        {"add",   add},
        {"addu",  addu},
        {"sub",   sub},
        {"subu",  subu},
        {"and",   andd},
        {"or",    orr},
        {"slt",   slt},
        {"sltu",  sltu}
    };

	return mapComandos;
}

map<string, IComando> addIComandos() {

    IComando beq{ "beq", 'I', 4, 0, 0, 0 };
    IComando bne{ "bne", 'I', 5, 0, 0, 0 };
    IComando addi{ "addi", 'I', 8, 0, 0, 0 };
    IComando addiu{ "addiu", 'I', 9, 0, 0, 0 };
    IComando slti{ "slti", 'I', 10, 0, 0, 0 };
    IComando sltiu{ "sltiu", 'I', 11, 0, 0, 0 };
    IComando andi{ "andi", 'I', 12, 0, 0, 0 };
    IComando ori{ "ori", 'I', 13, 0, 0, 0 };
    IComando lui{ "lui", 'I', 15, 0, 0, 0 };
    IComando lw{ "lw", 'I', 35, 0, 0, 0 };
    IComando sw{ "sw", 'I', 44, 0, 0, 0 };

    map<string, IComando> mapComandos = {
        {"beq",   beq},
        {"bne",   bne},
        {"addi",  addi},
        {"addiu", addiu},
        {"slti",  slti},
        {"sltiu", sltiu},
        {"andi",  andi},
        {"ori",   ori},
        {"lui",   lui},
        {"lw",    lw},
        {"sw",    sw}
    };

    return mapComandos;
}

map<string, int> addRegistradores() {

	map<string, int> mapRegs = { 
        {"$zero", 0}, {"$0", 0},   {"$at", 1},  {"$v0", 2}, {"$2", 2},
        {"$v1", 3},   {"$3", 3},   {"$a0", 4},  {"$4", 4},  {"$a1", 5 }, 
        {"$5", 5},    {"$a2", 6},  {"$6", 6},   {"$a3", 7}, {"$7", 7},
        {"$t0", 8},   {"$8", 8},   {"$t1", 9},  {"$9", 9},
        {"$t2", 10},  {"$10", 10}, {"$t3", 11}, {"$11", 11},
        {"$t4", 12},  {"$12", 12}, {"$t5", 13}, {"$13", 13},
        {"$t6", 14},  {"$14", 14}, {"$t7", 15}, {"$15", 15},
        {"$s0", 16},  {"$16", 16}, {"$s1", 17}, {"$17", 17},
        {"$s2", 18},  {"$18", 18}, {"$s3", 19}, {"$19", 19},
        {"$s4", 20},  {"$20", 20}, {"$s5", 21}, {"$21", 21},
        {"$s6", 22},  {"$22", 22}, {"$s7", 23}, {"$23", 23},
        {"$t8", 24},  {"$24", 24}, {"$t9", 25}, {"$25", 25},
        {"$k0", 26},  {"$26", 26}, {"$k1", 27}, {"$27", 27},
        {"$gp", 28},  {"$28", 28}, {"$sp", 29}, {"$29", 29},
        {"$fp", 30},  {"$30", 30}, {"$ra", 31}, {"$31", 31}
    };
	return mapRegs;
};
