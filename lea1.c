#include<stdio.h>  
#include<stdlib.h>
#include<stdint.h>
#define uintptr_t unsigned long int;
typedef uintptr_t coro_context[10];
#if defined(__APPLE__)
#define ASM_SYMBOL(name_) "_" #name_
#else
#define ASM_SYMBOL(name_) #name_
#endif

#define ASM_MY_FUNCTION(name_)                                                     \
    ".globl " ASM_SYMBOL(name_) "\n\t" ASM_SYMBOL(name_) ":\n\t"

#if defined(__x86_64__)
long* __attribute__((noinline, visibility("internal")))
leaqfunc(void *str1, void *str2);
asm(".text\n\t"
    ".p2align 5\n\t"
    ASM_MY_FUNCTION(leaqfunc)
    //"leaq 0x8(%rdi,%rsi,8), %rax \n\t"
    "leaq 0x8(%rdi), %rax \n\t"
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
	
	long * ptr = (long*)malloc(8*sizeof(long));

	for(int i =0;i<8;i++)
		ptr[i]= i+10;
	void* count=(void *)0;
	//printf("&ptr  = %p \n",(void *)ptr);
	//printf("&count  = %p \n",(void *)&count);
	printf("num1 = %ld\n",ptr[0]);
    void* num=(void*)leaqfunc((void*)ptr,count);
	
	//printf("num  = %p \n",num);
	printf("num  = %d \n",*(int*)num);
	return 0;
}  
