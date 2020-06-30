#ifndef _HANDLE_WAV_
#define _HANDLE_WAV_
#include <vector>

std::vector<float> readWavData(std::string fileName, bool verbose);
void writeWavFile(std::string fileName, const std::vector<float>& data, bool verbose);

#endif /* _HANDLE_WAV_ */
