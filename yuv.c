/*
 * arm-eabi-gcc -c -march=armv7-a -mfloat-abi=softfp -mfpu=neon rgb.c
 */

void yv12_yuv444(unsigned char *src, unsigned char *dst, int wid, int hei)
{
        __asm__ volatile (
                "       stmdb        sp!, {r4-r9}\r\n"
                "       mov          r4, %[w]\r\n"
                "       mul          r4, r4, %[h]\r\n"
                "       add          r5, %[s], %[w]\r\n"
                "       add          r6, %[s], r4\r\n"          /*V base*/
                "       add          r7, r6, r4, lsr #2\r\n"    /*U base*/
                "       add          r4, %[d], %[w], lsl #2\r\n"
                "       vmov.i8      d3, #0xff\r\n"
                "       vmov.i8      d7, #0xff\r\n"
                "1:     mov          r8, %[w]\r\n"
                "2:     vld1.8       {d0}, [%[s]]!\r\n"
                "       vld1.8       {d4}, [r5]!\r\n"
                "       ldr          r9, [r7], #4\r\n"
                "       vmov         d1, r9, r9\r\n"
                "       vmov         d5, r9, r9\r\n"
                "       vzip.8       d1, d5\r\n"
                "       ldr          r9, [r6], #4\r\n"
                "       vmov         d2, r9, r9\r\n"
                "       vmov         d6, r9, r9\r\n"
                "       vzip.8       d2, d6\r\n"
                "       vst4.8       {d0, d1, d2, d3}, [%[d]]!\r\n"
                "       vst4.8       {d4, d5, d6, d7}, [r4]!\r\n"
                "       subs         r8, r8, #8\r\n"
                "       bne          2b\r\n"
                "       add          %[s], %[s], %[w], lsl #1\r\n"
                "       add          r5, r5, %[w], lsl #1\r\n"
                "       add          %[d], %[d], %[w], lsl #3\r\n"
                "       add          r4, r4, %[w], lsl #2\r\n"
                "       subs        %[h], %[h], #2\r\n"
                "       bne          1b\r\n"
                "       ldmia        sp!, {r4-r9}\r\n"
        :: [s] "r" (src), [d] "r" (dst), [w] "r" (wid), [h] "r" (hei)
        );
}

