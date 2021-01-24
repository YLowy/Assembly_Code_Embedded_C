#include<stdio.h>  

#if defined(__APPLE__)
#define ASM_SYMBOL(name_) "_" #name_
#else
#define ASM_SYMBOL(name_) #name_
#endif

#define ASM_MY_FUNCTION(name_)                                                     \
    ".globl " ASM_SYMBOL(name_) "\n\t" ASM_SYMBOL(name_) ":\n\t"

#if defined(__x86_64__)
char* __attribute__((noinline, visibility("internal")))
leaqfunc(char* str);
asm(".text\n\t"
    ".p2align 5\n\t"
    ASM_MY_FUNCTION(leaqfunc)
	//"movq %rdi, %r12 \n\t"
    "leaq 0x8(%rdi), %r13 \n\t"
	//"addq $2 , %r13\n\t"
	"movq %r13, %rax \n\t"
    "ret \n\t"
	);
#elif defined(__aarch64__)
char* __attribute__((noinline, visibility("internal")))
Addfunc(int a, int b);
asm(".text\n\t"
	".globl Addfunc \n\t"
	"Addfunc:\n\t"
	"ADD x0,x0,x1\n\t"
	"ret\n\t"	
	);
#endif

int main() {  
    int a = 10,b=11;
	char *c;
	char  str[10] = {'a','b','c','d','e','f','g','h','e','\0'};
    
	printf("str  = %s \n",str);
	
	printf("&str  = %d \n",*(int*)(void*)&str);
	printf("&str+1  = %d \n",*(int*)(void*)(&str+8));
	
	c=leaqfunc(str);
	
	printf("c  = %s \n",c);
	printf("&c  = %d \n",*(int*)(void*)&c);
	return 0;
}  
