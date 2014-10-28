#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#define __cpuid__(in,eax,ebx,ecx,edx) \
		asm volatile( "pushl %%eax;"\
					  "pushl %%ebx;"\
					  "pushl %%ecx;"\
					  "pushl %%edx;"\
					  "movl %4 , %%eax ;"\
					  "xorl %%ebx , %%ebx ;"\
					  "xorl %%ecx , %%ecx ;"\
					  "xorl %%edx , %%edx ;"\
					  "cpuid ;"\
					  "movl %%eax ,%0 ;"\
					  "movl %%ebx ,%1 ;"\
					  "movl %%ecx ,%2 ;"\
					  "movl %%edx ,%3 ;"\
					  "popl %%edx;"\
					  "popl %%ecx;"\
					  "popl %%ebx;"\
					  "popl %%eax;"\
                     :"=m"(eax),"=m"(ebx),"=m"(ecx),"=m"(edx):"r"(in))

char * cpuid()
{
    static char cpuid_str[32]={0};
    unsigned int eax,ebx,ecx,edx;
    
    __cpuid__(0,eax,ebx,ecx,edx);
    eax &= 0xffff;
    if (eax < 3) {
    	sprintf(cpuid_str,"0000000000000000");
    	return cpuid_str;
    }
    __cpuid__(1,eax,ebx,ecx,edx);
    snprintf(cpuid_str,32,"%08X%08X", ntohl(eax),ntohl(edx));
    
    return cpuid_str;
}

int main()
{
	printf("cpu id %s\n",cpuid());
	return 0;
}
