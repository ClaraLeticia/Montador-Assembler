#include <iostream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <string>
#include <fstream>
#include <map>

using namespace std;

map<string, int> identificandoLabels(string inputArquivo) {
	ifstream fin(inputArquivo, ios_base::in); // abrir arquivo assembly pra leitura
	string input; // variavel para armazenar a linha de instrução
	string label;
	vector<string> labelVetor;
    int linha = 1;
    map<string, int>mapLabels;

    while (getline(fin, input)) {
        stringstream ss(input);
        linha++;
        size_t pos = input.find(':');
        if (pos != string::npos) { // Verifica se a linha contém ':'
            linha--; // Instrução necessária pois pela restrição de ser uma linha apenas pro label
            label = input.substr(0, pos); // Pega o valor antes dos dois pontos
            mapLabels[label] = linha; 
        }


    }

    fin.close();

    return mapLabels;

	
}