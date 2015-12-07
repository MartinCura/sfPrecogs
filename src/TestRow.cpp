/*
 * TestRow.cpp
 *
 *  Created on: 28 de nov. de 2015
 *      Author: guidonegri
 */

#include "TestRow.h"

TestRow::TestRow(int districtValue, int yearValue, int monthValue, int dayOfWeekValue, int hourValue, int cuadValue, int cuad2Value) {
	r_district = districtValue;
	r_dayWeek = dayOfWeekValue;
	r_anio = yearValue;
	r_mes = monthValue;
	r_hora = hourValue;
	r_cuad = cuadValue;
	r_cuad2 = cuad2Value;
}

int TestRow::getFeatureRow(TipoFeature tipo){
	switch (tipo){
	case DISTRICT: return r_district;
	case DAYWEEK: return r_dayWeek;
	case ANIO: return r_anio;
	case MES: return r_mes;
	case HORA: return r_hora;
	case CUAD: return r_cuad;
	case CUAD2: return r_cuad2;
	default: throw std::exception();
	}
}

TestRow::~TestRow() {
	// TODO Auto-generated destructor stub
}

