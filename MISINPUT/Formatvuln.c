#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <unistd.h>


void init(){
    setbuf(stdin, NULL);
    setbuf(stdout, NULL);
    setbuf(stderr, NULL);
    }   

void vuln(){


    char input_buffer[20];
    char secret[16] = "HEYHOWSITGOINGYO";

    printf("Hey how's it going, this challenge is just a lil warmup, just a lil something y'know ;)");
    printf("So we gonna be doing a little printf argument shenanigans :)");
    read(0, input_buffer, 64);
    printf(input_buffer);
        
}


int main(){
    init();
    vuln();


return 0;
}