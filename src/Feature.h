/*
 * Feature.h
 *
 *  Created on: 27 de nov. de 2015
 *      Author: guidonegri
 */

#ifndef FEATURE_H_
#define FEATURE_H_

class Feature {
private:

public:
    int cantidad;
	int sumatoria;
    double varianza;

	double getMedia();
	double getVarianza();

	Feature();
	virtual ~Feature();
};

#endif /* FEATURE_H_ */
