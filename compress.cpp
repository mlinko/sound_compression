#include <iostream>
#include <fstream>
#include <queue>
#include <cmath>
#include <string>
#include "dct.h"
#include "compress.h"

/*
std::vector<float> coeffin;
std::vector<float> coeffout;
*/

void filterCoeffs(float *coeffs, size_t N, size_t topCount, size_t window)
{
	size_t windowOffset = 0;

	while(windowOffset + window < N)
	{
		std::priority_queue<std::pair<float, size_t>> q;
		for (size_t i = 0; i < window and (windowOffset+i < N); i++)
		{
			q.push(std::pair<float, size_t>(coeffs[windowOffset + i],windowOffset+i));
		}

		int rank = 1;
		while(not q.empty())
		{
			if (rank > topCount)
			{
				coeffs[q.top().second] = 0.0f;
			}
			q.pop();

			rank++;
		}
		windowOffset += window;
	}
}

void compressDct(std::vector<float> data, size_t window, size_t components, std::string compressedFile)
{
	size_t N = data.size();
	std::vector<float> coeffs(N);
	
	discreteCosineTransform(&data[0], &coeffs[0], window, N);

	filterCoeffs(&coeffs[0], N, components, window);
	std::vector<float> data2(N);
//	inverseCosineTransform (&coeffs[0], &data2[0], window, N);

	float distance = 0.0f;
	for (int i = 0; i< N; i++)
		distance += (data[i]-data2[i]) * (data[i]-data2[i]);
	distance = pow(distance, 0.5);

	std::ofstream file(compressedFile, std::ios::binary);
	file.write((char*)&N, sizeof(size_t));
	file.write((char*)&window, sizeof(size_t));

	//coeffin = std::vector<float>(coeffs.begin(), coeffs.end());

	for (size_t i = 0; i < coeffs.size(); i++)
	{
		file.write((char*)&coeffs[i], sizeof(float));
		if (coeffs[i] == 0.0f)
		{
			size_t zeroCount = 1;
			while(coeffs[i+zeroCount] == 0.0f and (i + zeroCount < coeffs.size()))
			{
				zeroCount++;
			}
			file.write((char*)&zeroCount, sizeof(size_t));
			i += zeroCount - 1;
		}
	}
	file.close();

	/*
	std::vector<float> trash = decompressDct(compressedFile);

	std::cout << "DEBUG, take out!!!" << std::endl;
	*/

}

std::vector<float> decompressDct(std::string fileName)
{
	std::ifstream file(fileName, std::ios::binary);
	size_t N, window;
	file.read((char*)&N, sizeof(size_t));
	file.read((char*)&window, sizeof(size_t));
	
	std::vector<float> coeffs(N);

	for (size_t i = 0; i < N and !file.eof(); i++)
	{
		file.read((char*)&coeffs[i], sizeof(float));
		if (coeffs[i] == 0.0f)
		{
			size_t zeroCount;
			file.read((char*)&zeroCount, sizeof(size_t));
			for (size_t j = 1; j < zeroCount; j++)
			{
				coeffs[i + j] = 0.0f;
			}
			i += zeroCount - 1;
		}
	}
	file.close();

	//coeffout = std::vector<float>(coeffs.begin(), coeffs.end());

	std::vector<float> data(N);
	inverseCosineTransform (&coeffs[0], &data[0], window, N);

	return data;
	
}

/*
std::vector<float> compressDctOld(std::vector<float> data, size_t window, size_t components, int coeff)
{
	
//	std::vector<double> ddata (data.begin(), data.end());
//
//	unsigned int windowCount = data.size()/window;
//
//	gsl_fft_real_wavetable *real = gsl_fft_real_wavetable_alloc(data.size());
//	gsl_fft_real_workspace *work = gsl_fft_real_workspace_alloc(data.size());
//
//	gsl_fft_real_transform(&ddata[0], 1, ddata.size(), real, work);
//
//	gsl_fft_real_wavetable_free(real);
//	std::cout << "opk" << std::endl;
//
//	gsl_fft_halfcomplex_wavetable *halfcomplex = gsl_fft_halfcomplex_wavetable_alloc(data.size());
//	gsl_fft_halfcomplex_inverse(&ddata[0],1, data.size(), halfcomplex, work);
//	
//    gsl_fft_real_workspace_free(work);
//	gsl_fft_halfcomplex_wavetable_free(halfcomplex);


	size_t windowCount = length(X)/window;

	std::vector<float> coeffs = discreteCosineTransform(data);

	selectCoeffs(coeffs,0.4*data.size());
	std::vector<float> data2 = inverseCosineTransform(coeffs);

	
	float distance = 0.0f;
	for (int i = 0; i< data.size(); i++)
		distance += data[i]-data2[i];
	distance /= data.size();


	return data2;
}
*/
