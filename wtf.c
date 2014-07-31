#include <stdio.h>
#include <unistd.h>
int main(void) 
{ 
    fork(); 
    fork() && fork() || fork(); 
    fork();
    puts("+");
    return 0; 
}

