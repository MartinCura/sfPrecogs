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
	int cantidad;
	int sumatoria;
	float media;
	float varianza;

public:
	int getCantidad();
	int getSumatoria();
	float getMedia();
	float getVarianza();

	Feature();
	virtual ~Feature();
};

#endif /* FEATURE_H_ */
