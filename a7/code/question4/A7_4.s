.pos 0x0
                 ld   $0x1028, r5         
                 ld   $0xfffffff4, r0     
                 add  r0, r5              
                 ld   $0x200, r0          
                 ld   0x0(r0), r0         
                 st   r0, 0x0(r5)         
                 ld   $0x204, r0          
                 ld   0x0(r0), r0         
                 st   r0, 0x4(r5)         
                 ld   $0x208, r0          
                 ld   0x0(r0), r0         
                 st   r0, 0x8(r5)         
                 gpc  $6, r6                  
                 j    0x300             
                 ld   $0x20c, r1          
                 st   r0, 0x0(r1)         
                 halt                     
.pos 0x200
                 .long 0x00000000         
                 .long 0x00000000         
                 .long 0x00000000         
                 .long 0x00000000         
.pos 0x300
                 ld   0x0(r5), r0         
                 ld   0x4(r5), r1         
                 ld   0x8(r5), r2         
                 ld   $0xfffffff6, r3     
                 add  r3, r0              
                 mov  r0, r3              
                 not  r3                  
                 inc  r3                  
                 bgt  r3, L6              
                 mov  r0, r3              
                 ld   $0xfffffff8, r4     
                 add  r4, r3              
                 bgt  r3, L6              
                 ld   $0x400, r3          
                 j    *(r3, r0, 4)        
.pos 0x330
                 add  r1, r2              
                 br   L7                  
                 not  r2                  
                 inc  r2                  
                 add  r1, r2              
                 br   L7                  
                 not  r2                  
                 inc  r2                  
                 add  r1, r2              
                 bgt  r2, L0              
                 ld   $0x0, r2            
                 br   L1                  
L0:              ld   $0x1, r2            
L1:              br   L7                  
                 not  r1                  
                 inc  r1                  
                 add  r2, r1              
                 bgt  r1, L2              
                 ld   $0x0, r2            
                 br   L3                  
L2:              ld   $0x1, r2            
L3:              br   L7                  
                 not  r2                  
                 inc  r2                  
                 add  r1, r2              
                 beq  r2, L4              
                 ld   $0x0, r2            
                 br   L5                  
L4:              ld   $0x1, r2            
L5:              br   L7                  
L6:              ld   $0x0, r2            
                 br   L7                  
L7:              mov  r2, r0              
                 j    0x0(r6)             
.pos 0x400
                 .long 0x00000330         
                 .long 0x00000384         
                 .long 0x00000334         
                 .long 0x00000384         
                 .long 0x0000033c         
                 .long 0x00000384         
                 .long 0x00000354         
                 .long 0x00000384         
                 .long 0x0000036c         
.pos 0x1000
                 .long 0x00000000         
                 .long 0x00000000         
                 .long 0x00000000         
                 .long 0x00000000         
                 .long 0x00000000         
                 .long 0x00000000         
                 .long 0x00000000         
                 .long 0x00000000         
                 .long 0x00000000         
                 .long 0x00000000         
