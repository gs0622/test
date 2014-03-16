/*
 * arm-eabi-gcc -c -march=armv7-a -mfloat-abi=softfp -mfpu=neon rgb.c
 */
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

