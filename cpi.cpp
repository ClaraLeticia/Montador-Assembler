#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include "cpi.h"
#include <vector>
#include <map>
using namespace std;

void calcularCPI() {
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
        getline(ss, comando, ','); // Lê o comando antes da vírgula
        ss >> clock; // Lê o valor de clock após a vírgula

        mapClock[comando] = clock;

    }

    fin.close();

    for (auto i : mapClock) {
        cout << i.first << " " << i.second << endl;
    }
}