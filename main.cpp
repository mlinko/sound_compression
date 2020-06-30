#include <iostream>
#include <string>
#include <stdexcept>
#include <fstream>
#include <boost/program_options.hpp>
#include "handle_wav.h"
#include "compress.h"

int main(int argc, char** argv)
{
	boost::program_options::options_description description("Options");
	description.add_options()
		("help,h","help message")
		("input,i", boost::program_options::value<std::string>()->required(), "input file")
		("output,o", boost::program_options::value<std::string>()->required(), "output file")
		("compress,C", "compress input to output")
		("decompress,D", "decompress input to output")
		("verbose,v", "verbose output")
		("components,c", boost::program_options::value<int>()->default_value(200), "compression option, top component count to keep per window")
		("window,w", boost::program_options::value<int>()->default_value(2048), "compression option, window size to work with");
	boost::program_options::variables_map variables;
	boost::program_options::store(boost::program_options::parse_command_line(argc, argv, description), variables);
	
	if (variables.count("help"))
	{
		std::cout << description << std::endl;
		return 1;
	}

	if (variables.count("compress") == variables.count("decompress"))
	{
		std::cout << "\tEither --compress or --decompress is required, but only one at a time!" << std::endl;
		return 1;
	}

	boost::program_options::notify(variables);
	bool verbose = false;
	if(variables.count("verbose")) verbose = true;
	

	if (variables.count("compress"))
	{
		std::vector<float> data;
		data = readWavData(variables["input"].as<std::string>(), verbose);

		if (verbose) // printing into file, to plot with GNU
		{
			std::ofstream of("input_wave");
			for (size_t i = 0; i < data.size(); i++)
				of << data[i] << std::endl;
			of.close();
		}
		compressDct(data, variables["window"].as<int>(), variables["components"].as<int>(), variables["output"].as<std::string>());
	}

	if (variables.count("decompress"))
	{
		std::vector<float> data;
		data = decompressDct(variables["input"].as<std::string>());
		writeWavFile(variables["output"].as<std::string>(), data, verbose);

		if (verbose)
		{
			std::ofstream of("output_comp");
			for (size_t i = 0; i < data.size(); i++)
				of << data[i] << std::endl;
			of.close();
		}
	}

	return 0;
}
