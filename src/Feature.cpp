/*
 * Feature.cpp
 *
 *  Created on: 27 de nov. de 2015
 *      Author: guidonegri
 */

#include "Feature.h"

double Feature::getMedia(){
    return this->sumatoria / (double) this->cantidad;
}

double Feature::getVarianza() {
    return this->varianza;
}

Feature::Feature() {
	this->cantidad = 0;
	this->sumatoria = 0;
	this->varianza = 0;
	// TODO Auto-generated constructor stub
}

Feature::~Feature() {
	// TODO Auto-generated destructor stub
}

