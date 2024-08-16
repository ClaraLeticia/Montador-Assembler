#include <vector>
#include <string>
#include <map>
using namespace std;

vector<int> regs(vector<string> registradores, map<string, int> mapRegis){
	vector<int> regis;
	for (auto i : registradores) {
		for (auto j : mapRegis) {
			if (i == j.first) {
				regis.push_back(j.second);
			}
		}
	}

	return regis;
}

