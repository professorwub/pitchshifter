/*
  ==============================================================================

    PhaseVocoder.h
    Created: 8 Nov 2018 1:09:03pm
    Author:  Warren Koontz

  ==============================================================================
*/

#pragma once

#include <vector>
#include <complex>
#include "PVwindow.h"

typedef std::complex<float> Cfloat;

class PhaseVocoder
{
public:
	PhaseVocoder();
	~PhaseVocoder();

	// Methods
	void process(float*, int);
	void reset(int);
	void sethopRatio(float);

private:
	int order; // order of FFT engine
	int windowLength; // length of FFT window
	bool firstTime;
	float hopRatio;

	std::vector<float> prevPhase;
	std::vector<float> outputPhase;
	std::vector<float> prevOLA;
	std::vector<float> fftMagnitude;
	std::vector<Cfloat> fftInput;
	std::vector<Cfloat> fftOutput;

	PVwindow sampleBuffer;
};