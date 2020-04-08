/*
  ==============================================================================

    shifter.h
    Created: 16 May 2019 12:54:19pm
    Author:  profw

  ==============================================================================
*/

#pragma once

#include "stft.h"
#include "istft.h"

class SHIFTER
{
public:
	SHIFTER();
	~SHIFTER() {}

	void init(int);
	void step(float*, int, float);

private:
	STFT stft;
	ISTFT istft;

	int windowlength;

	std::vector<Cfloat> fftdata;
	std::vector<float> fftmag;
	std::vector<float> fftphase;
	std::vector<float> oldphase;
	std::vector<float> modphase;
	std::vector<float> deltaphase;
	bool firsttime;
};