#include <string>
#include <iostream>
#include "handle_wav.h"
#include <sndfile.hh>

std::vector<float> readWavData(std::string fileName, bool verbose)
{
	SndfileHandle fileHandle (fileName.c_str());

	if (verbose)
	{
		printf ("Opened file '%s'\n", fileName.c_str()) ;
		printf ("    Sample rate : %d\n", fileHandle.samplerate ()) ;
		printf ("    Channels    : %d\n", fileHandle.channels ()) ;
	}
	

	if (fileHandle.channels () != 1)
	{
		throw std::invalid_argument("Only one channel is supported");
	}

	std::vector<float> data(fileHandle.frames());
	fileHandle.readf(&data[0], int(fileHandle.frames()));

	return data;
}

void writeWavFile(std::string fileName, const std::vector<float>& data, bool verbose)
{
	size_t chanelCount = 1;
	size_t sampleRate = 8000;
	SndfileHandle fileHandle (fileName, SFM_WRITE, SF_FORMAT_WAV | SF_FORMAT_PCM_16 , chanelCount, sampleRate);
	
	int success = fileHandle.writef(&data[0], data.size());
	
	if (verbose)
		std::cout << "Writing " << fileName << "returned with " << success << std::endl;
}
