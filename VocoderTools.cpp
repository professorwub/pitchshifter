/*
  ==============================================================================

    VocoderTools.cpp
    Created: 13 Nov 2018 12:03:10pm
    Author:  profw

  ==============================================================================
*/

#include "VocoderTools.h"
#include <cmath>

void PVresample(float *x, int Nx, float *y, int Ny)
{
	float ratio = float(Nx - 1) / float(Ny - 1);
	y[0] = x[0];
	y[Ny - 1] = x[Nx - 1];
	for (int n = 1; n < Ny - 1; n++)
	{
		float xn = ratio * float(n);
		int n1 = int(floor(xn));
		y[n] = x[n1] + (xn - floor(xn)) * (x[n1 + 1] - x[n1]);
	}
}