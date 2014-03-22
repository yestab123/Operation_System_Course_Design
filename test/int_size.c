#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct int_size{
    unsigned char i;
};

struct int_size test;

int main(){
    test.i=255;
    printf("%d",test.i);
}
