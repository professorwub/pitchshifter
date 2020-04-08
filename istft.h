/*
  ==============================================================================

    istft.h
    Created: 4 May 2019 10:23:02am
    Author:  profw

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include <complex>
#include <vector>
#include <memory>

typedef std::complex<float> Cfloat;

class ISTFT
{
public:
	ISTFT() {}
	~ISTFT() {}

	void init(int);
	void step(Cfloat*, float*, int);

private:
	int windowlen;

	std::vector<float> sampleframe;
	std::vector<float> hannwindow;
	std::vector<Cfloat> fftoutput;

	float hannsum;

	std::unique_ptr<dsp::FFT> fft;
};