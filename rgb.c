/*
 * arm-eabi-gcc -c -march=armv7-a -mfloat-abi=softfp -mfpu=neon rgb.c
 */
#if 0
/** rgb_convert
 *
 *  convert RGB565 to RGB888, 8 pixels per loop
 *
 *  Note: version-1 reduce from 79 to 16.5 ms
 */
void rgb_convert(unsigned short *src, unsigned int *dst, unsigned int pxs)
{
        __asm__ volatile (
                "       cmp          %[s], #0\r\n"
                "       beq          2f\r\n"
                "       vmov.i32     d5, #0\r\n"
                "1:     vldmia       %[i]!, {q0}\r\n"
                "       vshr.u8      q1, q0, #3\r\n"
                "       vshrn.i16    d4, q1, #5\r\n"
                "       vshrn.i16    d3, q0, #5\r\n"
                "       vshl.i8      d3, d3, #2\r\n"
                "       vshl.i16     q0, q0, #3\r\n"
                "       vmovn.i16    d2, q0\r\n"
                "       vst4.8       {d2, d3, d4, d5}, [%[o]]!\r\n"
                "       subs         %[s], %[s], #8\r\n"
                "       bne          1b\r\n"
                "2:\r\n"
        :: [i] "r" (src), [o] "r" (dst), [s] "r" (pxs)
        );
}
#else
/** rgb_convert
 *
 *  convert RGB565 to RGB888, 16 pixels per loop
 *
 *  Note: version-1 reduce from 79 to 16.5 ms, version-2 down to 8.5 ms
 */

void rgb_convert(unsigned short *src, unsigned int *dst, unsigned int pxs)
{
        __asm__ volatile (
                "       cmp          %[s], #0\r\n"
                "       beq          2f\r\n"
                "       vmov.i32     d21, #0\r\n"
                "       vmov.i32     d27, #0\r\n"
                "1:     vldmia       %[i]!, {q8}\r\n"
                "       vldmia       %[i]!, {q11}\r\n"
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
        :: [i] "r" (src), [o] "r" (dst), [s] "r" (pxs)
        );
}
#endif
