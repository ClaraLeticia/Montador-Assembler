#include <iostream>
#include <string>
#include <map>
#include <bitset>
#include "Comandos.h"
using namespace std;

map<string, Comando> Comandos() {
    // Comandos tipo R
    Comando sll{ "sll", 'R', 0, 0, 0, 0, 0, 0 };
    Comando srl{ "srl", 'R', 0, 0, 0, 0, 0, 2 };
    Comando jr{ "jr", 'R', 0, 0, 0, 0, 0, 8 };
    Comando mfhi{ "mfhi", 'R', 0, 0, 0, 0, 0, 16 };
    Comando mflo{ "mflo", 'R', 0, 0, 0, 0, 0, 18 };
    Comando mult{ "mult", 'R', 0, 0, 0, 0, 0, 24 };
    Comando multu{ "multu",'R', 0, 0, 0, 0, 0, 25 };
    Comando div{ "div", 'R', 0, 0, 0, 0, 0, 26 };
    Comando divu{ "divu", 'R', 0, 0, 0, 0, 0, 27 };
    Comando add{ "add", 'R', 0, 0, 0, 0, 0, 32 };
    Comando addu{ "addu", 'R', 0, 0, 0, 0, 0, 33 };
    Comando sub{ "sub", 'R', 0, 0, 0, 0, 0, 34 };
    Comando subu{ "subu", 'R', 0, 0, 0, 0, 0, 35 };
    Comando andd{ "and", 'R', 0, 0, 0, 0, 0, 36 }; // ja tem and no c++
    Comando orr{ "or", 'R', 0, 0, 0, 0, 0, 37 }; // ja tem or
    Comando slt{ "slt", 'R', 0, 0, 0, 0, 0, 42 };
    Comando sltu{ "sltu", 'R', 0, 0, 0, 0, 0, 43 };
    Comando mul{ "mul", 'R', 28, 0, 0, 0, 0, 2};

    // Comandos tipo I
    Comando beq{ "beq", 'I', 4, 0, 0, 0, 0, 0 };
    Comando bne{ "bne", 'I', 5, 0, 0, 0, 0, 0 };
    Comando addi{ "addi", 'I', 8, 0, 0, 0, 0, 0  };
    Comando addiu{ "addiu", 'I', 9, 0, 0, 0, 0, 0 };
    Comando slti{ "slti", 'I', 10, 0, 0, 0, 0, 0 };
    Comando sltiu{ "sltiu", 'I', 11, 0, 0, 0, 0, 0 };
    Comando andi{ "andi", 'I', 12, 0, 0, 0, 0, 0 };
    Comando ori{ "ori", 'I', 13, 0, 0, 0, 0, 0 };
    Comando lui{ "lui", 'I', 15, 0, 0, 0, 0, 0 };
    Comando lw{ "lw", 'I', 35, 0, 0, 0, 0, 0 };
    Comando sw{ "sw", 'I', 43, 0, 0, 0, 0, 0 };

    // Comandos tipo J
    Comando j{ "j", 'J', 2, 0, 0, 0, 0, 0 };
    Comando jal{ "jal", 'J', 3, 0, 0, 0, 0, 0 };

	map<string, Comando> mapComandos = { 
        // Comandos tipo R
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
        {"sltu",  sltu},
        {"mul",   mul},

        // Comandos tipo I
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
        {"sw",    sw},

        // Comandos tipo J
        {"j",     j },
        {"jal",   jal}
    };

    return mapComandos;
  
}

map<string, int> addRegistradores() {

	map<string, int> mapRegs = { 
        {"$zero", 0}, {"$0", 0},   {"$at", 1}, {"$1", 1}, { "$v0", 2 }, {"$2", 2},
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
