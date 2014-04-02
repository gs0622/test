#include <stdio.h>

#define MIN(X,Y) (((X) < (Y)) ? (X) : (Y))
    
int main(int argc, char **argv)
{
    const int n = 20; // Generate n numbers
    int i, v[20], hamming,  hx2, hx5;
    int i2 = 0, i5 = 0;
    v[0] = 1;
    // Next two hamming candidates
    hx2 = 2 * v[i2];
    hx5 = 5 * v[i5];
    printf("%d ", v[0]);
    for (i = 1; i != n; ++i)
    {
        hamming = MIN(hx2, hx5);
        printf("%d ", hamming);
        v[i] = hamming;
        if (hx2 == hamming)
        {
            ++i2;
            hx2 = 2 * v[i2];
        }
        if (hx5 == hamming)
        {
            ++i5;
            hx5 = 5 * v[i5];
        }
        printf(" (%d-%d) ", i2, i5);
    }
    printf("\n");
    return 0;
}

/* out: 1 2 4 5 8 10 16 20 25 32 40 50 64 80 100 125 128 160 200 250

1 2  (1-0) 4  (2-0) 5  (2-1) 8  (3-1) 10  (4-2) 16  (5-2) 20  (6-3) 25  (6-4) 32
0  (11-7) 100  (12-8) 125  (12-9) 128  (13-9) 160  (14-10) 200  (15-11) 250  (16-

 */
