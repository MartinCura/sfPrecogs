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
#include "ClasificadorBayesiano.h"
#include "ParserCSV.h"
#include "TestRow.h"
#include <sstream>
#include <fstream>
#include <string>

using namespace std;

int main() {
	cout << "MAAIAAAMEEEEE" << endl;

	string train = "train1611.csv";
	string test = "test1911SinId.csv";
	string sub = "submission.csv";
	int CANT_ROW_TEST = 20;//884262;

	ParserCSV* parser = new ParserCSV(train, test, sub);

	vector<Crimen*>* v_crimenes = parser->parseTrain();

	///////////////////////////////////////////////////////////////
	//PARA PROBAR EL CONTADOR DE CRIMENES:
//	int xx = 0;
//	for ( vector<Crimen*>::iterator it = v_crimenes->begin(); it != v_crimenes->end(); ++it ) {
//		Crimen* crimen = *it;
//		fprintf(stderr, "EL CRIMEN %d aparece: %ld veces!\n", xx, crimen->apariciones);
//		xx++;
//	}
    /////////////////////////////////////////////////////////////

	ClasificadorBayesiano* clasificador = new ClasificadorBayesiano(v_crimenes);

	for (int i = 0; i < CANT_ROW_TEST; i++){
		TestRow* row_test = parser->getNextTestRow();
		if (row_test) {
			vector<long double>* probas = clasificador->predictProba(row_test);
			delete row_test;
			parser->writeRowSubmission(probas);
		}
	}
	parser->closeSubmission();

    delete clasificador;
    v_crimenes->clear();
    delete v_crimenes;
    delete parser;

	return 0;
}
