/*
 * Filename: rangeCheck.s
 * Author: Jialu Xu
 * UserId: cs30s219ci
 * Date: 2019.8.12
 * Sources of help: PA1 Writeup.
 */

@ Raspberry Pi directives
        .cpu    cortex-a53                  @Version of our Pis
        .syntax unified                     @Modern ARM syntax

        .equ    FP_OFFSET, 4                @offset from sp to set fp
        .global rangeCheck                  @Specify rangeCheck as global

        .text                               @Switch to Text segment
        .align  2                           @Align on evenly divisible by 4 
                                            @bytes address

/*
 * Function Name: rangeCheck
 * Function Prototype: long rangeCheck(long value, long minRange,
                        long maxRange)
 * Description: This function checks whether the given value in the 
                        given range
 * Parameters: r0 - value -    the given value
 *             r1 - minRange - the lower bound of the range, inclusive
 *             r2 - maxRange - the upper bound of the range, exclusive
 * Error Conditions: minRange is greater than or equal to maxRange
 * Return value: 0 if not in range; 1 if in range; -1 if error
 */



rangeCheck:
@Standard prologue
        push    {fp, lr}                    @save caller's fp and lr
        add     fp, sp, FP_OFFSET           @set fp to point ti base of saved 
        
        
        cmp     r1, r2                      @minRange >=  maxRange
        bge     error                       @opposite logic test to branch over
                                            @if statements

        cmp     r0, r1                      @value < minRange
        blt     else                        @opposite logic to branch over if
                                            @statements

        cmp     r0, r2                      @value >= maxRange
        bge     else                        @opposite logic to branch over if 
                                            @statements
        mov     r0, 1                       @both expressions are true

        b       end                         @branch always over else block
else:
        mov     r0, 0                       @one or both of the expressions
                                            @are false
        b       end
error: 
        mov     r0, -1                      @return -1 when there's an error

end:
        sub     sp, fp, FP_OFFSET           @set sp to top of saved regs
        pop     {fp, pc}                    @restore fp and return
        
