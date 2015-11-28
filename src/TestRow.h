/*
 * TestRow.h
 *
 *  Created on: 28 de nov. de 2015
 *      Author: guidonegri
 */

#ifndef TESTROW_H_
#define TESTROW_H_

class TestRow {
private:
	int r_district;
	int r_dayWeek;
	int r_anio;
	int r_mes;
	int r_hora;
	int r_cuad;

public:
	TestRow();

	int getFeatureRow(TipoFeature tipo);

	virtual ~TestRow();
};

#endif /* TESTROW_H_ */
