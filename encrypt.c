#include<stdlib.h>
#include<string.h>
#include<stdio.h>
 
void encrypt(char *data, const char *key)
{
    int i;
    int len = strlen(key);
    while (*data) {
        for (i = 0; i < len; i++) {
            *data= *data ^ (int)key[i];
        }
        data++;
    }
}
 
int main(int argc, char *argv[])
{
    char s[] = "hehe123";
    char *key = "!@#$%";
	
    /*encrypt*/
    encrypt(s, key);
    printf("encrypt :%s\n", s);
    
    /*decrypt*/
    encrypt(s, key);
    printf("decrypt:%s\n", s);
 
    return 0;
} 
