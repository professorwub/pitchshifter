/*
  ==============================================================================

    stft.h
    Created: 4 May 2019 10:22:48am
    Author:  profw

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include <complex>
#include <vector>
#include <memory>

typedef std::complex<float> Cfloat;

class STFT
{
public:
	STFT() {}
	~STFT() {}

	void init(int);
	void step(float*, int, Cfloat*);

private:
	int windowlen;

	std::vector<float> sampleframe;
	std::vector<float> hannwindow;
	std::vector<Cfloat> fftinput;

	std::unique_ptr<dsp::FFT> fft;
};