/* 
 * File name: hash.s
 * Author: Jialu Xu
 * UserId: cs30s219ci
 * Date: 2019.8.22
 * Sources of help: PA3 Writeup.
 */



@ Raspberry Pi directives
        .cpu    cortex-a53                  @Version of our Pis
        .syntax unified                     @Modern ARM syntax

@ define some magic number
        .equ    FP_OFFSET, 4                @offset from sp to set fp
        
@ define space for local variables
        .equ    LOCAL_VAR_SPACE, 8          @allocate the space for local 
                                            @variables
        .equ    HASH_OFFSET, -8             @local variable: hash
        .equ    STRLEN_OFFSET, -12          @local variable: strlen

@ define space for formal parameters        
        .equ    PARAMETER_SPACE, 8          @allocate the space for formal
                                            @parameters
        .equ    STR_OFFSET, -16             @1st formal parameter


        .global hash                        @Specify hash as global

        .text                               @Switch to Text segment
        .align  2                           @Align on evenly divisible by 4 
                                            @bytes address

/*
 * Function Name: hash
 * Function Prototype: int hash( char *str )
 * Description: This function will be used to create the hash key of a string. 
 * Parameters: r0 - str - the given string
 * Return value: the harsh key of str.
 */


hash:
        push    {fp, lr}                    @save caller's fp and lr
        add     fp, sp, FP_OFFSET           @set fp to point tO base of saved 
                                            @regs
        sub     sp, sp, LOCAL_VAR_SPACE     @allocate the space for local vars
        sub     sp, sp, PARAMETER_SPACE     @allocate the space for parameters
        str     r0, [fp, STR_OFFSET]        @store the first parameter 
                                            @into stack
@initialize hash
        ldr     r0, =HashStartVal
        ldr     r0, [r0]
        str     r0, [fp, HASH_OFFSET]

@initialize strlen
        ldr     r0, [fp, STR_OFFSET]
        bl      strlen
        str     r0, [fp, STRLEN_OFFSET]

@iterate through the length of input string and update the hash value
        
        ldr     r3, [fp, STR_OFFSET]        @r3=ptr
        ldr     r2, [fp, STRLEN_OFFSET]     @r2=strlen
        add     r2, r2, r3                  @r2=end_ptr=ptr+strlen

        cmp     r3, r2                      @while(r3>=r2)
        bge     end_loop                    @opposite logic to skip the loop

loop:   
        ldr     r0, [fp, HASH_OFFSET]
        ldr     r1, =HashPrime
        ldr     r1, [r1]
        mul     r0, r0, r1
        str     r0, [fp, HASH_OFFSET]      @hash=hash*HashPrime

        ldrb    r0, [r3]       
        ldr     r1, [fp, HASH_OFFSET]      @hash=hash+str[i]
        add     r0, r0, r1
        str     r0, [fp, HASH_OFFSET]

        add     r3, r3, 1

        cmp     r3, r2                     @while(r3<r2)
        blt     loop                       @positive logic go back to loop

end_loop:
        ldr     r0, [fp, HASH_OFFSET]

        sub     sp, fp, FP_OFFSET           @set sp to top of saved regs
        pop     {fp, pc}    



