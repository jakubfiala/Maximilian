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
#include <algorithm>
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
    
    double* loudness(float* powerSpectrum, std::string type) {
        bbLimits[0] = 0;
        int currentBandEnd = barkScale[specSize-1]/NUM_BARK_BANDS;
        int currentBand = 1;
        
        for(int i = 0; i<specSize; i++){
            while(barkScale[i] > currentBandEnd) {
                bbLimits[currentBand++] = i;
                currentBandEnd = currentBand*barkScale[specSize-1]/NUM_BARK_BANDS;
            }
        }
        
        bbLimits[NUM_BARK_BANDS] = specSize-1;
        
        if (type == "specific") {
            for (int i = 0; i < NUM_BARK_BANDS; i++){
                double sum = 0;
                for (int j = bbLimits[i] ; j < bbLimits[i+1] ; j++) {
                    
                    sum += normalisedSpectrum[j];
                }
                specificLoudness[i] = Math.pow(sum,0.23);
            }
            
            return specificLoudness;
        }
        else if (type == "relative") {
            for (int i = 0; i < NUM_BARK_BANDS; i++){
                double sum = 0;
                for (int j = bbLimits[i] ; j < bbLimits[i+1] ; j++) {
                    
                    sum += normalisedSpectrum[j];
                }
                specificLoudness[i] = Math.pow(sum,0.23);
            }
            
            double max = std::max_element(specificLoudness[0], specificLoudness[23]);
            
            for (int i = 0; i < NUM_BARK_BANDS; i++){
                relativeLoudness[i] = max/specificLoudness[i];
            }
            
            return relativeLoudness;
        }
        else { //default is total
            for (int i = 0; i < NUM_BARK_BANDS; i++){
                double sum = 0;
                for (int j = bbLimits[i] ; j < bbLimits[i+1] ; j++) {
                    
                    sum += normalisedSpectrum[j];
                }
                specificLoudness[i] = Math.pow(sum,0.23);
            }
            
            for (int i = 0; i < 24; i++){
                totalLoudness += specificLoudness[i];
            }
            
            return totalLoudness;
        }
        
        
        
    }
private:
    int* bbLimits;
    unsigned int sampleRate, bufferSize, specSize;
    double* barkScale;
    double* specificLoudness, totalLoudness, relativeLoudness;
    
};






