#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define IS123 0x01
#define ISTTT 0x03

#define IS_TEST(x) ((x & (IS123))?1:0)

struct int_size{
    int te:8;
};

struct int_size test;

int main(){
    test.te=ISTTT;
    printf("%d\n",test.te);
    if(IS_TEST(test.te))
    {
        printf("123\n");
    }
    return 0;
}
