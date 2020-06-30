#ifndef _COMPRESS_
#define _COMPRESS_
#include <vector>

void filterCoeffs(float *coeffs, size_t N, size_t topCount, size_t window);
void compressDct(std::vector<float> data, size_t window, size_t components, std::string compressedFile);
std::vector<float> decompressDct(std::string fileName);

#endif /* _COMPRESS_ */
