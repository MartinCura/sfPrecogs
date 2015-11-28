/*
 * ClasificadorBayesiano.h
 *
 *  Created on: 27 de nov. de 2015
 *      Author: guidonegri
 */

#ifndef CLASIFICADORBAYESIANO_H_
#define CLASIFICADORBAYESIANO_H_

#include <string>
#include <vector>
#include <math.h>
#include "Crimen.h"
#include "TestRow.h"
using namespace std;

class ClasificadorBayesiano {
private:
	vector<Crimen*>* crimenes;
	vector<double>* probabilidades;

public:
	ClasificadorBayesiano(vector<Crimen*>* v_crimenes);

	double calcularProbaCondicional(int valor_row, double var_crimen, double media_crimen);

	vector<double>* predictProba(TestRow* row);

	virtual ~ClasificadorBayesiano();
};

#endif /* CLASIFICADORBAYESIANO_H_ */
