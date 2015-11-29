/*
 * Crimen.h
 *
 *  Created on: 27 de nov. de 2015
 *      Author: guidonegri
 */

#ifndef CRIMEN_H_
#define CRIMEN_H_

#include "Feature.h"
#include "Enum.h"

class Crimen {
private:

public:
    Feature* f_district;
	Feature* f_dayWeek;
	Feature* f_anio;
	Feature* f_mes;
	Feature* f_hora;
	Feature* f_cuad;
	long apariciones = 1;   // Cantidad de veces presente en el train dataset.
    double proba_crimen;

	double getMedia(TipoFeature tipo);
	double getVarianza(TipoFeature tipo);
	double getProbaCrimen();

	Crimen();
	virtual ~Crimen();
};

#endif /* CRIMEN_H_ */
