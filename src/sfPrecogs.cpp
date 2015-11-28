//============================================================================
// Name        : sfPrecogs.cpp
// Author      : Precogs
// Version     :
// Copyright   : Robar es malo.
// Description : TP Organización de Datos (75.06)
//============================================================================

#include <stdio.h>
#include <vector>
#include <iostream>
#include <vector>
#include "Statistics.h"
#include <sstream>
#include <fstream>
#include <string>

using namespace std;

/*Para leer el csv, no esta funcionando:
 	std::vector<std::string> getNextLineAndSplitIntoTokens(std::istream& str)
{
    std::vector<std::string> result;
    std::string line;
    std::getline(str,line);
    std::stringstream lineStream(line);
    std::string cell;

    while(std::getline(lineStream,cell,','))
    {
        result.push_back(cell);
    }
    return result;
}
*/

int main() {
	// Saludos
	cout << "MAAIAAAMEEEEE" << endl;

	// lectura de train
		float mean = 5.855;
		vector<float> x;
		x.push_back(6);
		x.push_back(5.92);
		x.push_back(5.58);
		x.push_back(5.92);
		float variance = 0;
		for (int i = 0; i < 4; ++i) {
	        variance += (x[i] - mean) * 2;
	    }

	    cout << variance;
	// Training

	// lectura de test
	// Predictions

	// Escritura

	// gracias totales
	return 0;
}


