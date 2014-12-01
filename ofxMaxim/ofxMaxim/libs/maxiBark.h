/*
 *  maxiBark.cpp
 *  Bark scale loudness
 *
 *  Created by Jakub on 01/12/2014.
 *  Copyright 2014 Goldsmiths Creative Computing. All rights reserved.
 *
 */

#pragma once
#pragma pack(16)

#include "maxiFFT.h"
#include <math.h>
#include <iostream>
#include <cstdlib>
#ifdef __APPLE_CC__
#include <Accelerate/Accelerate.h>
#endif

using namespace std;

//convert to Bark scale (Zwicker, 1961)
inline double hzToBark(double hz) {
    return 13.0*atan(hz/1315.8) + 3.5*atan(pow((hz/7518.0),2));
}

inline double binToHz(unsigned int bin, unsigned int sR, unsigned int bS) {
    return bin*sR/bS;
}

template <class T>

class maxiBarkScaleAnalyser {
public:
    const int NUM_BARK_BANDS = 24;
    
    void setup(unsigned int sR, unsigned int bS) {
        this->sampleRate = sR;
        this->bufferSize = bS;
        specSize = sR/2;
        for (int i=0; i<specSize; i++) {
            barkScale[i] = hzToBark(binToHz(i));
        }
    }
    
    void loudness(float* powerSpectrum) {
        
        
        
    }
private:
    int* bbLimits;
    unsigned int sampleRate, bufferSize, specSize;
    double* barkScale;
    
};






