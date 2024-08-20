#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include "cpi.h"
#include <vector>
#include <map>
#include "Comandos.h"
using namespace std;

void calcularCPI(map<string, Comando> qtdComandos ) {
    fstream fin;
    string input;
    string linha;
    stringstream ss;
    
    map<string, int> mapClock;

	fin.open("ciclos.csv");

    getline(fin, input);

    while (getline(fin, linha)) {
        string comando;
        int clock;

        stringstream ss(linha);
        getline(ss, comando, ','); // L� o comando antes da v�rgula
        ss >> clock; // L� o valor de clock ap�s a v�rgula

        mapClock[comando] = clock;

    }

    fin.close();
    int soma = 0, n = 0;

    cout << "Quantidades por tipo de instru��es:" << endl;
    for (auto i : qtdComandos) {
        if (i.second.ocorrencias != 0) {
            cout << i.first << ": " << i.second.ocorrencias << " " << endl;
            for (auto j : mapClock) {
                if (i.first == j.first) {  
                    soma+= i.second.ocorrencias * j.second;
                    break;
                }
            }
            n++;
        }
    }
    
    cout << endl << "CPI m�dio:" << soma / float(n);

}