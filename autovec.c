/* arm-eabi-gcc -g -c -march=armv7-a -mfpu=neon -mfloat-abi=softfp -ftree-vectorize -O2 autovec.c
 */
/*example11:
 *  feature: support strided accesses - the data elements
 *  that are to be operated upon in parallel are not consecutive - they
 *  are accessed with a stride > 1 (in the example, the stride is 2): 
 */
#define N       1024
void ex1(int *a, int *b, int *c, int *d)
{
        int i;
        for (i=0; i<N/2; i++){
                a[i] = b[2*i+1] * c[2*i+1] - b[2*i] * c[2*i];
                d[i] = b[2*i] * c[2*i+1] + b[2*i+1] * c[2*i];
        }
}

#define SIZE    1024
void ex2(float * __restrict data1, float * __restrict data2, float * __restrict out)
{
        int i;
        for(i=0; i<SIZE*4; i+=1) {
                out[i] = data1[i]*data2[i];
        }
}

