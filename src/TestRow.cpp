/*
 * TestRow.cpp
 *
 *  Created on: 28 de nov. de 2015
 *      Author: guidonegri
 */

#include "TestRow.h"



TestRow::TestRow() {
	r_district = 0;
	r_dayWeek = 0;
	r_anio = 0;
	r_mes = 0;
	r_hora = 0;
	r_cuad = 0;
}

int TestRow::getFeatureRow(TipoFeature tipo){
	switch (tipo){
	case DISTRICT: return r_district;
	case DAYWEEK: return r_dayWeek;
	case ANIO: return r_anio;
	case MES: return r_mes;
	case HORA: return r_hora;
	case CUAD: return r_cuad;
	default: break;
	}
}

TestRow::~TestRow() {
	// TODO Auto-generated destructor stub
}

