
        
#include <sys/asm.h>
#include <sys/regdef.h>

LEAF(gThreadSelf)

        .set noreorder
        .set noat

        lui a3,32
        ori a3,a3,3804
        lw a3,0(a3)

        lui v0,2
        addiu v0,v0,5216

        lw t8, %call16(pthread_self)($gp)
        
        beq a3,zero,xxx
        addu AT,t8,v0

        li v1,344
        lw a0,-31832(AT)
        subu a0,a3,a0
        div $0,a0,v1

        teq v1,zero,7
        
        mflo v0

        jr ra
        andi v0,v0,65535

xxx:    
        lui v0,0
        jr ra

       

END(gThreadSelf)


/*
        .set reorder
        lui a3,32
        ori a3,a3,3804
        lw a3,0(a3)
        lui v0,2
        addiu v0,v0,5216
        beq a3,zero,xxx
      addu AT,t9,v0 # comment out
        li v1,344
        lw a0,-31832(AT)
        subu a0,a3,a0
        div $0,a0,v1
        teq v1,zero,7
        lw v1,20(a3)
        lui a0,65535
        and v1,v1,a0
        mflo v0
        andi v0,v0,65535
        jr ra
        or v0,v0,v1

xxx:    
        lui v0,1
        jr ra
*/
