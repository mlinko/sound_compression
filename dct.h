#ifndef _DCT_H_
#define _DCT_H_
void discreteCosineTransform(float *data, float *coeffs, unsigned int windowSize, unsigned int N);
void inverseCosineTransform(float *coeffs, float *data, unsigned int windowSize, unsigned int N);

#endif /* _DCT_H_ */

