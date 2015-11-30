/*
 * ClasificadorBayesiano.cpp
 *
 *  Created on: 27 de nov. de 2015
 *      Author: guidonegri
 */

#include "ClasificadorBayesiano.h"
#include <stdio.h> //dsp sacar
#include <iostream>  //dsp sacar
using namespace std; //dsp sacar

ClasificadorBayesiano::ClasificadorBayesiano(vector<Crimen*>* v_crimenes) {
	crimenes = v_crimenes;
	probabilidades = new vector<long double>();
	probabilidadesConEvidencia = new vector<long double>();
}

vector<long double>* ClasificadorBayesiano::predictProba(TestRow* row){
	probabilidades->clear();
	int CANT_CRIMENES = 39;
	int CANT_FEATURES = 6;
	// For para cada CRIMEN:
	for (int i = 0; i < CANT_CRIMENES; i++){
		//cout << "CRIMEN NRO: " << i << endl;//
		Crimen* crimen = crimenes->at(i);
		long double proba_crimen = crimen->getProbaCrimen();
		//cout << "Proba: " << crimen->getProbaCrimen() << endl;//
		vector<long double> proba_condicional;

		//proba_condicional.push_back(1);	/// PARA SALTEAR UNA FEATURE, descomentar y cambiar el valor inicial de j por 1
		// For para cada FEATURE:
		for (int j = 0/*1*/; j < CANT_FEATURES; j++){
			long double varianza_feature = crimen->getVarianza(TipoFeature(j));
			//cout << "VARIANZA: " << varianza_feature << " del Feature: " << j << endl;

			long double media_feature = crimen->getMedia(TipoFeature(j));
			//cout << "MEDIA: " << media_feature << " del Feature: " << j << endl;

			int valor_row = row->getFeatureRow(TipoFeature(j));
			//cout << "VALOR_ROW: " << valor_row << " del Feature: " << j << endl;

			long double proba = this->calcularProbaCondicional(valor_row, varianza_feature, media_feature);			//<<<<<<<<<<<<<<<<<<<<<<

			proba_condicional.push_back(proba);
		}

		// Calculo posteriori:
		long double posteriori = proba_crimen;
		for (int k = 0; k < CANT_FEATURES; k++){
			posteriori = posteriori * proba_condicional.at(k);
		}
		proba_condicional.clear();

		//cout << "El posteriori del crimen es: " << posteriori << endl;//
		probabilidades->push_back(posteriori);
	}
	return this->dividirPorEvidencia(probabilidades);
	// para bubi:
	//return probabilidades;
}

/*
long double ClasificadorBayesiano::calcularProbaCondicionalViejo(int valor_row, long double var_f, long double media_f){
	const long double PI = 3.141592653589793238463;
	long double error = 1;
	if (var_f == 0) return error; //No deberia haber varianza = 0, pero hay un caso que pasaba.

	long double division = 1 / sqrt(2 * PI * var_f);
	long double exponente_paso1 = - (pow(valor_row - media_f, 2));
	long double exponente_paso2 = exponente_paso1 / (2 * var_f);
	long double proba_cond = pow(division, exponente_paso2);

	if (! isfinite(proba_cond)) return error;	// Comentable si se arregla lo otro
	return proba_cond;
}
*/

long double ClasificadorBayesiano::calcularProbaCondicional(int valor_row, long double var_f, long double media_f){
	const long double PI = 3.141592653589793238463;
	long double error = 1;
	if (var_f == 0) return error; //No deberia haber varianza = 0, pero hay un caso que pasaba.

	long double division = 1 / sqrt(2 * PI * var_f);
	long double exponente_paso1 = - (pow(valor_row - media_f, 2));
	long double exponente_paso2 = exponente_paso1 / (2 * var_f);
	long double proba_cond = division * exp( exponente_paso2 );

    if (! isfinite(proba_cond)) return error;
	return proba_cond;
}

vector<long double>* ClasificadorBayesiano::dividirPorEvidencia(vector<long double>* posterioris){
	probabilidadesConEvidencia->clear();
	long double error = 1;
	long double evidencia = 0;

    for ( vector<long double>::iterator it = posterioris->begin(); it != posterioris->end(); ++it ) {
        long double posteriori = *it;
        evidencia += posteriori;
        //cout << "Evidencia parcial: " << evidencia << endl;//
    }
    long double sumatoriaAux = 0;//
    for ( vector<long double>::iterator it = posterioris->begin(); it != posterioris->end(); ++it ) {
         long double probaFinal = (*(it)) / evidencia;
         //cout << "*****Proba real del crimen es: " << probaFinal << endl;//
         if (! isfinite(probaFinal)) probaFinal = error;
         probabilidadesConEvidencia->push_back(probaFinal);
         sumatoriaAux += probaFinal;//
    }
    //cout << "~~~Sumatoria de probas finales: "<<sumatoriaAux<<std::endl;//
    return probabilidadesConEvidencia;
}

ClasificadorBayesiano::~ClasificadorBayesiano() {
	probabilidades->clear();
	delete probabilidades;
	probabilidadesConEvidencia->clear();
	delete probabilidadesConEvidencia;
}

