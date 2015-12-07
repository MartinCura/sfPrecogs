/*
 * TestRow.h
 *
 *  Created on: 28 de nov. de 2015
 *      Author: guidonegri
 */

#ifndef TESTROW_H_
#define TESTROW_H_

#include "Enum.h"

class TestRow {
private:
	int r_district;
	int r_dayWeek;
	int r_anio;
	int r_mes;
	int r_hora;
	int r_cuad;
	int r_cuad2;

public:
	TestRow(int districtValue, int yearValue, int monthValue, int dayOfWeekValue, int hourValue, int cuadValue, int cuad2Value);

	int getFeatureRow(TipoFeature tipo);

	virtual ~TestRow();
};

#endif /* TESTROW_H_ */
