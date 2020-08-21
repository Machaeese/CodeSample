/* 
 * File name: llTableAddString.s
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
        .equ    POINTER_SIZE, 4
        
@ define space for local variables
        .equ    LOCAL_VAR_SPACE, 16         @allocate the space for local 
                                            @variables
        .equ    HASH_OFFSET, -8             @local variable: hash
        .equ    INDEX_OFFSET, -12           @local variable: index
        .equ    SIZE_OFFSET, -16            @local variable: size

@ define space for formal parameters        
        .equ    PARAMETER_SPACE, 8          @allocate the space for formal
                                            @parameters
        .equ    TABLE_OFFSET, -20           @1st formal parameter
        .equ    STR_OFFSET, -24             @2nd formal parameter


        .global llTableAddString            @Specify llTableAddString as global

        .text                               @Switch to Text segment
        .align  2                           @Align on evenly divisible by 4 
                                            @bytes address

/*
 * Function Name: llTableAddString
 * Function Prototype: void llTableAddString( table_t *table, char *string )
 * Description: This function calls table->hashFunction() to hash string.  
 * Parameters: r0 - table - the given table
 *             r1 - string - the given string to be hashed
 * Return value: Null
 */


llTableAddString:
        push    {fp, lr}                    @save caller's fp and lr
        add     fp, sp, FP_OFFSET           @set fp to point tO base of saved 
                                            @regs
        sub     sp, sp, LOCAL_VAR_SPACE     @allocate the space for local vars
        sub     sp, sp, PARAMETER_SPACE     @allocate the space for parameters
        str     r0, [fp, TABLE_OFFSET]      @store the first parameter 
                                            @into stack
        str     r1, [fp, STR_OFFSET]        @store the first parameter
                                            @into stack

@get the hash_key populated by hashFunction
        ldr     r1, [fp, TABLE_OFFSET]
        ldr     r2, =HashFunctionOffset
        ldr     r2, [r2]
        ldr     r1, [r1, r2]
        ldr     r0, [fp, STR_OFFSET]
        blx     r1
        str     r0, [fp, HASH_OFFSET]

@get the table size
        ldr     r0, [fp, TABLE_OFFSET]
        ldr     r1, =SizeOffset
        ldr     r1, [r1]
        ldr     r0, [r0, r1]
        str     r0, [fp, SIZE_OFFSET]

@get the index by calculating
        ldr     r0, [fp, HASH_OFFSET]
        ldr     r1, [fp, SIZE_OFFSET]
        bl      getRemainder                @hash=hash%table_size
        str     r0, [fp, HASH_OFFSET]

        ldr     r0, [fp, HASH_OFFSET]
        ldr     r1, [fp, SIZE_OFFSET]
        add     r0, r0, r1
        str     r0, [fp, HASH_OFFSET]       @hash=hash+table_size

        ldr     r0, [fp, HASH_OFFSET]
        ldr     r1, [fp, SIZE_OFFSET]
        bl      getRemainder                @idx=hash%table_size
        mov     r2, POINTER_SIZE
        mul     r0, r0, r2
        str     r0, [fp, INDEX_OFFSET]

@get the address of the indexth node in llArray in table
        
        ldr     r0, [fp, TABLE_OFFSET]
        ldr     r2, =ArrayOffset
        ldr     r2, [r2]
        ldr     r0, [r0, r2]
        ldr     r1, [fp, INDEX_OFFSET]
        add     r0, r0, r1                 
        ldr     r1, [fp, STR_OFFSET]
        bl      prependNode

        sub     sp, fp, FP_OFFSET           @set sp to top of saved regs
        pop     {fp, pc}    



