#include<stdio.h>  

#if defined(__APPLE__)
#define ASM_SYMBOL(name_) "_" #name_
#else
#define ASM_SYMBOL(name_) #name_
#endif

#define ASM_MY_FUNCTION(name_)                                                     \
    ".globl " ASM_SYMBOL(name_) "\n\t" ASM_SYMBOL(name_) ":\n\t"

#if defined(__x86_64__)
int __attribute__((noinline, visibility("internal")))
Addfunc(int a, int b);
asm(".text\n\t"
    ".p2align 5\n\t"
    ASM_MY_FUNCTION(Addfunc)
	"movq %rdi, %r12 \n\t"
	"movq %rsi, %r13 \n\t"
    "addq %r12, %r13 \n\t"
	"movq %r13, %rax \n\t"
    "ret \n\t"
	);
#elif defined(__arm__)
int __attribute__((noinline, visibility("internal")))
Addfunc(int a, int b);
asm(
	"Addfunc:\n\t"
	"ADD r0,r0,r1\n\t"
	"BX  lr\n\t"
	);
#endif

int main() {  
    int a = 10,b=11,c;
    printf("Addfunction\n");
	c=Addfunc(a,b);
	
	printf("a = %d b = %d \n",a,b);
	printf("a+b  = %d \n",c);
	return 0;
}  
