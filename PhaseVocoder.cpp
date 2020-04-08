/*
  ==============================================================================

    PhaseVocoder.cpp
    Created: 8 Nov 2018 1:09:03pm
    Author:  profw

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "PhaseVocoder.h"
#include "VocoderTools.h"
#include <cmath>

PhaseVocoder::PhaseVocoder()
{
	hopRatio = 1.0;
	firstTime = true;
}

PhaseVocoder::~PhaseVocoder()
{
}

void PhaseVocoder::process(float *samples, int numSamples)
{
	// major declarations
	float pi = 3.14159;
	dsp::FFT fftEngine(order);
	dsp::FFT ifftEngine(order);

	// push samples into buffer
	sampleBuffer.shiftIn(samples, numSamples);

	// copy window buffer into FFT input buffer, applying root-Hanning window
	for (int n = 0; n < windowLength; n++)
		fftInput[n] = sampleBuffer[n] * sin(pi * float(n) / float(windowLength));

	// compute FFT amplitude and phase
	fftEngine.perform(fftInput.data(), fftOutput.data(), false);
	for (int n = 0; n < windowLength; n++)
	{
		fftMagnitude[n] = abs(fftOutput[n]);
		float fftPhase = arg(fftOutput[n]);
		// adjust phase using vocoder algorithm
		if (firstTime)
		{
			outputPhase[n] = fftPhase;
			firstTime = false;
		}
		else
		{
			float unwrap = fftPhase - prevPhase[n] - 2.0 * pi * float(numSamples) * float(n) / float(windowLength);
			unwrap -= 2.0 * pi * round(unwrap / (2.0f * pi));
			unwrap = (unwrap + 2.0 * pi * float(numSamples) * float(n) / float(windowLength)) * hopRatio;
			outputPhase[n] = outputPhase[n] + unwrap;
		}
		prevPhase[n] = fftPhase;
	}
	// compute modified FFT and its inverse
	for (int n = 0; n < windowLength; n++)
		fftInput[n] = std::polar(fftMagnitude[n], outputPhase[n]);
	ifftEngine.perform(fftInput.data(), fftOutput.data(), true);
	// apply window to IFFT
	for (int n = 0; n < windowLength; n++)
		fftOutput[n] *= sin(pi * float(n) / float(windowLength));
	// calculate synthesis length
	int synthesisLength = int(round(float(numSamples) * hopRatio));
	std::vector<float> synthSamples (synthesisLength, 0.0);
	// calculate gain
	float Gain = 2.0 * float(synthesisLength) / float(windowLength);
	// overlap add
	for (int n = 0; n < windowLength - synthesisLength; n++)
		fftOutput[n] += prevOLA[n];
	for (int n = 0; n < windowLength - synthesisLength; n++)
		prevOLA[n] = fftOutput[n + synthesisLength].real();
	for (int n = 0; n < synthesisLength; n++)
		synthSamples[n] = fftOutput[n].real() * Gain;
	// resample
	PVresample(synthSamples.data(), samples, synthesisLength, numSamples);
}

void PhaseVocoder::reset(int samplesPerBlock)
{
	// window size and FFT order
	order = 0;
	windowLength = 1;
	while (windowLength < 8 * samplesPerBlock)
	{
		order++;
		windowLength *= 2;
	}
	// reset containers
	prevPhase.assign(windowLength, 0.0);
	outputPhase.assign(windowLength, 0.0);
	prevOLA.assign(windowLength, 0.0);
	fftInput.assign(windowLength, 0.0);
	fftOutput.assign(windowLength, 0.0);
	fftMagnitude.assign(windowLength, 0.0);

	sampleBuffer.setSize(windowLength);

	firstTime = true;
}

void PhaseVocoder::sethopRatio(float semiTones)
{
	hopRatio = pow(2.0, semiTones / 12.0);
}
