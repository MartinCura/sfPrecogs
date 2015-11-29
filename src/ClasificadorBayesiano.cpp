/*
 * ClasificadorBayesiano.cpp
 *
 *  Created on: 27 de nov. de 2015
 *      Author: guidonegri
 */

#include "ClasificadorBayesiano.h"

ClasificadorBayesiano::ClasificadorBayesiano(vector<Crimen*>* v_crimenes) {
	crimenes = v_crimenes;
	probabilidades = new vector<double>();

}

vector<double>* ClasificadorBayesiano::predictProba(TestRow* row){
	int CANT_CRIMENES = 40;
	int CANT_FEATURES = 6;
	// For para cada CRIMEN:
	for (int i = 0; i < CANT_CRIMENES; i++){
		Crimen* crimen = *crimenes[i];
		double proba_crimen = crimen->getProbaCrimen();
		vector<double> proba_condicional;

		// For para cada FEATURE:
		for (int j = 0; j < CANT_FEATURES; j++){
			double varianza_feature = crimen->getVarianza(TipoFeature(j));
			double media_feature = crimen->getMedia(TipoFeature(j));
			int valor_row = row->getFeatureRow(TipoFeature(j));
			double proba = this->calcularProbaCondicional(valor_row, varianza_feature, media_feature);
			proba_condicional.push_back(proba);
		}

		// Calculo posteriori:
		double posteriori = proba_crimen;
		for (int k = 0; k < CANT_FEATURES; k++){
			posteriori = posteriori * proba_condicional[k];
		}
		probabilidades->push_back(posteriori);
	}
	return probabilidades;
}

double ClasificadorBayesiano::calcularProbaCondicional(int valor_row, double var_f, double media_f){
	const double PI = 3.141592653589793238463;
	double division = 1 / sqrt(2 * PI * var_f);

	double exponente_paso1 = - (pow(valor_row - media_f, 2));
	double exponente_paso2 = exponente_paso1 / (2 * var_f);
	double proba_cond = pow(division, exponente_paso2);

	return proba_cond;
}

ClasificadorBayesiano::~ClasificadorBayesiano() {
	// TODO Auto-generated destructor stub
}

