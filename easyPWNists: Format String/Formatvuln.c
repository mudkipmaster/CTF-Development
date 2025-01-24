#include <stdio.h>
#include <stdlib.h>

void init(){
    setbuf(stdin, NULL);
    setbuf(stdout, NULL);
    setbuf(stderr, NULL);
    }   

void vuln(){
    printf("Hey how's it going, this challenge is just a lil warmup, just a lil something y'know ;)");
    printf("So we gonna be doing a little printf argument shenanigans :)");
    

    
}



int main(){
    init();
    


return 0;
}