/*
 * Feature.cpp
 *
 *  Created on: 27 de nov. de 2015
 *      Author: guidonegri
 */

#include "Feature.h"

long double Feature::getMedia(){
    return this->sumatoria / (long double) this->cantidad;
}

long double Feature::getVarianza() {
    return this->varianza;
}

Feature::Feature() {
	this->cantidad = 0;
	this->sumatoria = 0;
	this->varianza = 0;
}

Feature::~Feature() {
	// TODO Auto-generated destructor stub
}

