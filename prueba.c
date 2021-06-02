
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


int main(int argc, char **argv) {
    
    dup2(1, 13);
    execv("./server", NULL);
    
}