/* File name: getRemainder.s
 * Author: Jialu Xu
 * UserId: cs30s219ci
 * Date: 2019.8.12
 * Sources of help: PA1 Writeup.
 */



@ Raspberry Pi directives
        .cpu    cortex-a53                  @Version of our Pis
        .syntax unified                     @Modern ARM syntax

        .equ    FP_OFFSET, 4                @offset from sp to set fp

        .global getRemainder                @Specify getRemainder as global

        .text                               @Switch to Text segment
        .align  2                           @Align on evenly divisible by 4 
                                            @bytes address

/*
 * Function Name: getRemainder
 * Function Prototype: long getRemainder(long dividend, long divisor)
 * Description: This function get the remainder of the given dividend divided
                by divisor
 * Parameters: r0 - dividend - the given dividend
 *             r1 - divisor  - the given divisor
 *             r2 - quotient - r2=r0/r1
 *             r3 - multi    - r3=r2*r1
 * Return value: the remainder
 */



getRemainder:
@Standard prologue
        push    {fp, lr}                    @save caller's fp and lr
        add     fp, sp, FP_OFFSET           @set fp to point ti base of saved 
        
        
        sdiv    r2, r0, r1                  @r2=r0/r1
        mul     r3, r2, r1                  @r3=r2*r1
        sub     r2, r0, r3                  @r2=r0-r3
        
        mov     r0, r2                      @save the remainder to r0

        sub     sp, fp, FP_OFFSET           @set sp to top of saved regs
        pop     {fp, pc}                    @restore fp and return
        
       
