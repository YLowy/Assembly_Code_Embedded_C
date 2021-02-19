#include<stdio.h>  
#include<stdlib.h>
#include<stdint.h>
#define uintptr_t unsigned long int;
#if defined(__APPLE__)
#define ASM_SYMBOL(name_) "_" #name_
#else
#define ASM_SYMBOL(name_) #name_
#endif
#define ASM_MY_FUNCTION(name_)                                                     \
    ".globl " ASM_SYMBOL(name_) "\n\t" ASM_SYMBOL(name_) ":\n\t"

#if defined(__x86_64__)
long* __attribute__((noinline, visibility("internal")))
coro_switch(void *curr, void *oth);
asm(".text\n\t"
    ".p2align 5\n\t"
    ASM_MY_FUNCTION(coro_switch)
    "movq   %rbx,0(%rdi)\n\t"
    "movq   %rbp,8(%rdi)\n\t"
    "movq   %r12,16(%rdi)\n\t"
    "movq   %r13,24(%rdi)\n\t"
    "movq   %r14,32(%rdi)\n\t"
    "movq   %r15,40(%rdi)\n\t"
    "movq   %rdi,48(%rdi)\n\t"
    "movq   %rsi,56(%rdi)\n\t"
    "movq   (%rsp),%rcx\n\t"
    "movq   %rcx,64(%rdi)\n\t"
    "leaq   0x8(%rsp),%rcx\n\t"
    "movq   %rcx,72(%rdi)\n\t"
    "movq   72(%rsi),%rsp\n\t"
    "movq   0(%rsi),%rbx\n\t"
    "movq   8(%rsi),%rbp\n\t"
    "movq   16(%rsi),%r12\n\t"
    "movq   24(%rsi),%r13\n\t"
    "movq   32(%rsi),%r14\n\t"
    "movq   40(%rsi),%r15\n\t"
    "movq   48(%rsi),%rdi\n\t"
    "movq   64(%rsi),%rcx\n\t"
    "movq   56(%rsi),%rsi\n\t"
    "jmpq   *%rcx\n\t");
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
struct coro
{
    void *switcher;
    unsigned long int context[20];
    unsigned char *stack;
};

typedef void* (*coro_function_t) (void* ptr,void* other);

void* coro_function1(void *current, void *other){

    printf("%d\n",*(int*)current);
    (*(int*)current) = (*(int*)current)  +1;
    coro_switch((void*)current,other);
}


struct coro *coro_new(void* switcher, coro_function_t func, void *data){
    struct coro * coro = malloc(sizeof(struct coro));

    coro->stack = malloc(sizeof(16384*4));
    /*For the coroutine space*/

    /*store the func and data ptr in the coro's context */
    coro->context[0] = (unsigned long int)func;// enter point
    coro->context[1] = (unsigned long int)data;//data
    coro->context[2] = (unsigned long int)switcher;//switcher
    coro->context[3] = coro->stack+16384*4 - 8;; // for the $rsp  
    coro->context[4] = 100; // the result in refer

    return coro;
}

int main() {  
	
    unsigned long int switcher[20];
    void* data1 = (void *)0xFF;
    void * current = (void*)0x11;
    struct coro *A = coro_new((void*)switcher, coro_function1, data1);
    coro_yeild(sw)
    return 0;
   
}  
