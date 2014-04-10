#include <stdio.h>
#include <strings.h>
#include <time.h>

static unsigned short src[540*960] __attribute__ ((__aligned__ (64)));
static unsigned int dst[540*960] __attribute__ ((__aligned__ (64)));

/* YT's 64 pixel version for Cortex-A15 */
void rgb_convert_yt_ca15(unsigned short *src, unsigned int *dst, unsigned int pxs)
{
        __asm__ volatile (
                "       lsrs        ip, r2, #6\r\n"
                "       vmov.i8     q3, #0\r\n"
                "       vmov.i8     q7, #0\r\n"
                "       beq         63f\r\n"
                "       vld2.8      {q1, q2}, [r0:256]!\r\n"
                "       vmov.i8     q11, #0\r\n"
                "       vpush       {q4-q7}\r\n"
                "       vld2.8      {q5, q6}, [r0:256]!\r\n"
                "       vld2.8      {q9, q10}, [r0:256]!\r\n"
                "       pld         [r0, #64]\r\n"
                "       vld2.8      {q13, q14}, [r0:256]!\r\n"
                "       pld         [r0, #64]\r\n"
                "       .align  4   @align to 16byte for CA15 L1I$ prefetcher\r\n"
                "64:    vmov.i8     q15, #7\r\n"
                "       vshl.i8     q0, q1, #3\r\n"
                "       pld         [r0, #384]\r\n"
                "       vshr.u8     q1, q1, #3\r\n"
                "       vshl.i8     q4, q5, #3\r\n"
                "       pld         [r0, #448]\r\n"
                "       vshr.u8     q5, q5, #3\r\n"
                "       vshl.i8     q8, q9, #3\r\n"
                "       subs        ip, ip, #1\r\n"
                "       vshr.u8     q9, q9, #3\r\n"
                "       vshl.i8     q12, q13, #3\r\n"
                "       vshr.u8     q13, q13, #3\r\n"
                "       vsli.8      q1, q2, #5\r\n"
                "       vbic        q2, q2, q15\r\n"
                "       vsli.8      q5, q6, #5\r\n"
                "       vbic        q6, q6, q15\r\n"
                "       vsli.8      q9, q10, #5\r\n"
                "       vbic        q10, q10, q15\r\n"
                "       vbic        q1, q1, q15\r\n"
                "       vsli.8      q13, q14, #5\r\n"
                "       vbic        q14, q14, q15\r\n"
                "       vbic        q5, q5, q15\r\n"
                "       vst4.8      {d0, d2, d4, d6}, [r1:256]!\r\n"
                "       vbic        q9, q9, q15\r\n"
                "       vst4.8      {d1, d3, d5, d7}, [r1:256]!\r\n"
                "       vbic        q13, q13, q15\r\n"
                "       vst4.8      {d8, d10, d12, d14}, [r1:256]!\r\n"
                "       vmov.i8     q15, #0\r\n"
                "       vst4.8      {d9, d11, d13, d15}, [r1:256]!\r\n"
                "       beq         640f\r\n"
                "       vst4.8      {d16, d18, d20, d22}, [r1:256]!\r\n"
                "       vld2.8      {q1, q2}, [r0:256]!\r\n"
                "       vst4.8      {d17, d19, d21, d23}, [r1:256]!\r\n"
                "       vld2.8      {q5, q6}, [r0:256]!\r\n"
                "       vst4.8      {d24, d26, d28, d30}, [r1:256]!\r\n"
                "       vld2.8      {q9, q10}, [r0:256]!\r\n"
                "       vst4.8      {d25, d27, d29, d31}, [r1:256]!\r\n"
                "       vld2.8      {q13, q14}, [r0:256]!\r\n"
                "       bne         64b\r\n"
                "640:   vst4.8      {d16, d18, d20, d22}, [r1:256]!\r\n"
                "       vst4.8      {d17, d19, d21, d23}, [r1:256]!\r\n"
                "       vst4.8      {d24, d26, d28, d30}, [r1:256]!\r\n"
                "       vst4.8      {d25, d27, d29, d31}, [r1:256]!\r\n"
                "       vpop        {q4-q7}\r\n"
                "63:    ands        r2, r2, #64\r\n"
                "       mov         r3, #0\r\n"
        );
}

/* YT's 32 pixel version for Cortex-A9 */
void rgb_convert_yt_ca9(unsigned short *src, unsigned int *dst, unsigned int pxs, unsigned pld)
{
        __asm__ volatile (
                "        lsrs    ip, r2, #5\r\n"
                "        vmov.i8 q15, #7\r\n"
                "        beq     31f\r\n"
                "        vld2.8  {q0, q1}, [r0:256]!\r\n"
                "        vld2.8  {q2, q3}, [r0:256]!\r\n"
                "        vmov.i8 q10, #0\r\n"
                "        vmov.i8 q14, #0\r\n"
                "        vpush   {q7}\r\n"
                "32:     vshr.u8 q8, q0, #3\r\n"
                "        pld     [r0, #256]\r\n"
                "        vshr.u8 q12, q2, #3\r\n"
                "        pld     [r0, #288]\r\n"
                "        vshl.i8 q7, q0, #3\r\n"
                "        vshl.i8 q11, q2, #3\r\n"
                "        vsli.8  q8, q1, #5\r\n"
                "        vsli.8  q12, q3, #5\r\n"
                "        vbic    q9, q1, q15\r\n"
                "        vbic    q13, q3, q15\r\n"
                "        vbic    q8, q8, q15\r\n"
                "        subs    ip, ip, #1\r\n"
                "        vbic    q12, q12, q15\r\n"
                "        beq     320f\r\n"
                "        vld2.8  {q0, q1}, [r0:256]!\r\n"
                "        vld2.8  {q2, q3}, [r0:256]!\r\n"
                "320:    vst4.8  {d14, d16, d18, d20}, [r1:256]!\r\n"
                "        vst4.8  {d15, d17, d19, d21}, [r1:256]!\r\n"
                "        vst4.8  {d22, d24, d26, d28}, [r1:256]!\r\n"
                "        vst4.8  {d23, d25, d27, d29}, [r1:256]!\r\n"
                "        bne     32b\r\n"
                "        vpop    {q7}\r\n"
                "31:\r\n"
        :: [i] "r" (src), [o] "r" (dst), [s] "r" (pxs)
        );
}

/* YT's 32 pixel version, modified by HP for cacheline 64B */
void rgb_convert_yt_c64(unsigned short *src, unsigned int *dst, unsigned int pxs, unsigned pld)
{
        __asm__ volatile (
                "        lsrs       ip, r2, #5\r\n"
                "        vmov.i8    q15, #7\r\n"
                "        beq        31f\r\n"
                "        vld2.8     {q0, q1}, [r0:256]!\r\n"
                "        vld2.8     {q2, q3}, [r0:256]!\r\n"
                "        vmov.i8    q10, #0\r\n"
                "        vmov.i8    q14, #0\r\n"
                "        vpush      {q7}\r\n"
                "32:     vshr.u8    q8, q0, #3\r\n"
                "        pld        [%[i], %[p]]\r\n"
                "        vshr.u8    q12, q2, #3\r\n"
                "        vshl.i8    q7, q0, #3\r\n"
                "        vshl.i8    q11, q2, #3\r\n"
                "        vsli.8  q8, q1, #5\r\n"
                "        vsli.8  q12, q3, #5\r\n"
                "        vbic    q9, q1, q15\r\n"
                "        vbic    q13, q3, q15\r\n"
                "        vbic    q8, q8, q15\r\n"
                "        subs    ip, ip, #1\r\n"
                "        vbic    q12, q12, q15\r\n"
                "        beq     320f\r\n"
                "        vld2.8  {q0, q1}, [r0:256]!\r\n"
                "        vld2.8  {q2, q3}, [r0:256]!\r\n"
                "320:    vst4.8  {d14, d16, d18, d20}, [r1:256]!\r\n"
                "        vst4.8  {d15, d17, d19, d21}, [r1:256]!\r\n"
                "        vst4.8  {d22, d24, d26, d28}, [r1:256]!\r\n"
                "        vst4.8  {d23, d25, d27, d29}, [r1:256]!\r\n"
                "        bne     32b\r\n"
                "        vpop    {q7}\r\n"
                "31:\r\n"
        :: [i] "r" (src), [o] "r" (dst), [s] "r" (pxs), [p] "r" (pld)
        );
}

/* YT's 32 pixel version, modified by HP for cacheline 32B */
void rgb_convert_yt_c32(unsigned short *src, unsigned int *dst, unsigned int pxs, unsigned pld)
{
        __asm__ volatile (
                "        lsrs       ip, r2, #5\r\n"
                "        vmov.i8    q15, #7\r\n"
                "        beq        31f\r\n"
                "        vld2.8     {q0, q1}, [r0:256]!\r\n"
                "        vld2.8     {q2, q3}, [r0:256]!\r\n"
                "        vmov.i8    q10, #0\r\n"
                "        vmov.i8    q14, #0\r\n"
                "        vpush      {q7}\r\n"
                "32:     vshr.u8    q8, q0, #3\r\n"
                "        pld        [%[i], %[p]]\r\n"
                "        add        %[p], %[p], #32\r\n"
                "        vshr.u8    q12, q2, #3\r\n"
                "        pld        [%[i], %[p]]\r\n"
                "        sub        %[p], %[p], #32\r\n"
                "        vshl.i8    q7, q0, #3\r\n"
                "        vshl.i8    q11, q2, #3\r\n"
                "        vsli.8  q8, q1, #5\r\n"
                "        vsli.8  q12, q3, #5\r\n"
                "        vbic    q9, q1, q15\r\n"
                "        vbic    q13, q3, q15\r\n"
                "        vbic    q8, q8, q15\r\n"
                "        subs    ip, ip, #1\r\n"
                "        vbic    q12, q12, q15\r\n"
                "        beq     320f\r\n"
                "        vld2.8  {q0, q1}, [r0:256]!\r\n"
                "        vld2.8  {q2, q3}, [r0:256]!\r\n"
                "320:    vst4.8  {d14, d16, d18, d20}, [r1:256]!\r\n"
                "        vst4.8  {d15, d17, d19, d21}, [r1:256]!\r\n"
                "        vst4.8  {d22, d24, d26, d28}, [r1:256]!\r\n"
                "        vst4.8  {d23, d25, d27, d29}, [r1:256]!\r\n"
                "        bne     32b\r\n"
                "        vpop    {q7}\r\n"
                "31:\r\n"
        :: [i] "r" (src), [o] "r" (dst), [s] "r" (pxs), [p] "r" (pld)
        );
}

/* HP's 16 pixel version */
void rgb_convert_hp(unsigned short *src, unsigned int *dst, unsigned int pxs, unsigned pld)
{
        __asm__ volatile (
                "       cmp          %[s], #0\r\n"
                "       beq          2f\r\n"
                "       vmov.i32     d21, #0\r\n"
                "       vmov.i32     d27, #0\r\n"
                "1:     vldmia       %[i]!, {q8}\r\n"
                "       vldmia       %[i]!, {q11}\r\n"
                "       pld          [%[i], %[p]]\r\n"
                "       vshr.u8      q9, q8, #3\r\n"
                "       vshr.u8      q12, q11, #3\r\n"
                "       vshrn.i16    d20, q9, #5\r\n"
                "       vshrn.i16    d26, q12, #5\r\n"
                "       vshrn.i16    d19, q8, #5\r\n"
                "       vshrn.i16    d25, q11, #5\r\n"
                "       vshl.i8      d19, d19, #2\r\n"
                "       vshl.i8      d25, d25, #2\r\n"
                "       vshl.i16     q8, q8, #3\r\n"
                "       vshl.i16     q11, q11, #3\r\n"
                "       vmovn.i16    d18, q8\r\n"
                "       vmovn.i16    d24, q11\r\n"
                "       vst4.8       {d18, d19, d20, d21}, [%[o]]!\r\n"
                "       vst4.8       {d24, d25, d26, d27}, [%[o]]!\r\n"
                "       subs         %[s], %[s], #16\r\n"
                "       bne          1b\r\n"
                "2:\r\n"
        :: [i] "r" (src), [o] "r" (dst), [s] "r" (pxs), [p] "r" (pld)
        );
}

typedef void (*func_t)(unsigned short *, unsigned int *, unsigned int, unsigned int);

int main(int argc, char **argv)
{
        int i, j;
        float t3;
        const int frames=10000;
        struct timespec t1, t2;
        func_t rgb565to888 = rgb_convert_hp;

        if (argc > 1) {
            if (argv[1][0]=='1') {
                printf("model: rgb_convert_yt_ca9\n\r");
                rgb565to888 = rgb_convert_yt_ca9;
            }
            if (argv[1][0]=='2') {
                printf("model: rgb_convert_yt_ca15\n\r");
                rgb565to888 = rgb_convert_yt_ca15;
            }
            if (argv[1][0]=='3') {
                printf("model: rgb_convert_yt_c32\n\r");
                rgb565to888 = rgb_convert_yt_c32;
            }
            if (argv[1][0]=='4') {
                printf("model: rgb_convert_yt_c64\n\r");
                rgb565to888 = rgb_convert_yt_c64;
            }
        }
        memset((void *)src, 0xff, 540*960*2);
        for (j=0; j<=1024; j+=32) {
                clock_gettime(CLOCK_REALTIME, &t1);
                for (i=0; i<frames; i++) {
                        rgb565to888(src, dst, 540*960, j);
                }
                clock_gettime(CLOCK_REALTIME, &t2);
                t3 = (float)(t2.tv_sec-t1.tv_sec)+(float)(t2.tv_nsec-t1.tv_nsec)/1000000000;
                printf("%.4d: %d frames\t%f s\t%f s/f\n", j, frames, t3, t3/(float)frames);
        }
        return 0;
}

