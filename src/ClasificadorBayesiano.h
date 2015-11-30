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
	vector<long double>* probabilidades;
	vector<long double>* probabilidadesConEvidencia;

public:
	ClasificadorBayesiano(vector<Crimen*>* v_crimenes);

	long double calcularProbaCondicional(int valor_row, long double var_crimen, long double media_crimen);
	//long double calcularProbaCondicionalViejo(int valor_row, long double var_f, long double media_f);

	vector<long double>* dividirPorEvidencia(vector<long double>* probas);

	vector<long double>* predictProba(TestRow* row);

	virtual ~ClasificadorBayesiano();
};

#endif /* CLASIFICADORBAYESIANO_H_ */
