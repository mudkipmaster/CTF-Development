#include <stdio.h>
#include <stdlib.h>
//barebones


void init(){
    setbuf(stdin, NULL);
    setbuf(stdout, NULL);
    setbuf(stderr, NULL);
}


void RattleMeBones(){
    printf("Barry thanks you for the kind words :)\n");
    system("cat Flag.txt");
}


void hes_so_boned(){

char input[16];

printf("Barry the Boneless is having trouble with some alignment problems.\n");
printf("He was given this number: %x, but it doesn't seem to work? \n", &RattleMeBones);
puts("Enter your words of encouragement for Barry so that he doesn't get too demotivated: ");
fgets(input, 100, stdin);

}

int main(){
    init();
    hes_so_boned();

return 0;
}