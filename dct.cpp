#include <cmath>
#include <iostream>
#include <vector>
#include <cstring>

/*  
 *  Calculates the DCT of each window
 */
void discreteCosineTransform(float *data, float *coeffs, unsigned int windowSize, unsigned int N)
{
	float *waveTable = new float[windowSize*windowSize];

	for (size_t k = 0; k < windowSize; k++)
	{
		for (size_t n = 0; n < windowSize; n++)
		{
			waveTable[k*windowSize + n] = cos(M_PI / windowSize * (n + 0.5) * k);
		}
	}

	unsigned int windowCount = N / windowSize;

	for ( size_t w = 0; w < windowCount; w++)
	{
		for (size_t k = 0; k < windowSize; k++)
		{
			for (size_t n = 0; n < windowSize; n++)
			{
				coeffs[w * windowSize + k] += data[w * windowSize + n] * waveTable[k * windowSize + n];
			}
		}
	}

	if (N % windowSize)
	{
		for (size_t k = 0; k < N - windowCount * windowSize; k++)
		{
			for (size_t n = 0; n < N - windowCount * windowSize; n++)
			{
				coeffs[windowCount * windowSize + k] += data[windowCount * windowSize + n] * waveTable[k * windowSize + n];
			}
		}
	}
	delete waveTable;
}


/*  
 *  Calculates the IDCT of each window
 */
void inverseCosineTransform(float *coeffs, float *data, unsigned int windowSize, unsigned int N)
{
	float *waveTable = new float[windowSize*windowSize];
	for (size_t k = 0; k < windowSize; k++)
	{
		for (size_t n = 0; n < windowSize; n++)
		{
			waveTable[k*windowSize + n] = cos(M_PI / windowSize * n * (k + 0.5));
		}
	}

	unsigned int windowCount = N / windowSize;

	for (size_t w = 0; w < windowCount; w++)
	{
		for (size_t k = 0; k < windowSize; k++)
		{
			data[w * windowSize + k] = 0.5 * coeffs[0];
			for (size_t n = 1; n < windowSize; n++)
			{
				data[w * windowSize + k] += coeffs[w * windowSize + n] * waveTable[k * windowSize + n];
			}
			data[w * windowSize + k] *= 2.0 / (float)windowSize;
		}
	}

	if (N % windowSize)
	{
		for (size_t k = 0; k < N - windowCount * windowSize; k++)
		{
			data[windowCount * windowSize + k] = 0.5 * coeffs[0];
			for (size_t n = 0; n < N - windowCount * windowSize; n++)
			{
				data[windowCount * windowSize + k] += coeffs[n] * waveTable[k * windowSize + n];
			}
			data[windowCount * windowSize + k] *= 2.0 / (float)windowSize;
		}
	}
	delete waveTable;
}

