/*
 * Crimen.cpp
 *
 *  Created on: 27 de nov. de 2015
 *      Author: guidonegri
 */

#include "Crimen.h"

Crimen::Crimen() {
	f_district = new Feature();
	f_dayWeek = new Feature();
	f_anio = new Feature();
	f_mes = new Feature();
	f_hora = new Feature();
	f_cuad = new Feature();
	proba_crimen = 0;
}

double Crimen::getMedia(TipoFeature tipo){
	switch (tipo){
	case DISTRICT: return f_district->getMedia();
	case DAYWEEK: return f_dayWeek->getMedia();
	case ANIO: return f_anio->getMedia();
	case MES: return f_mes->getMedia();
	case HORA: return f_hora->getMedia();
	case CUAD: return f_cuad->getMedia();
	default: break;
	}
}

double Crimen::getVarianza(TipoFeature tipo){
	switch (tipo){
	case DISTRICT: return f_district->getVarianza();
	case DAYWEEK: return f_dayWeek->getVarianza();
	case ANIO: return f_anio->getVarianza();
	case MES: return f_mes->getVarianza();
	case HORA: return f_hora->getVarianza();
	case CUAD: return f_cuad->getVarianza();
	default: break;
	}
}

double Crimen::getProbaCrimen(){
	return proba_crimen;
}

Crimen::~Crimen() {
	delete f_district;
	delete f_dayWeek;
	delete f_anio;
	delete f_mes;
	delete f_hora;
	delete f_cuad;
}

