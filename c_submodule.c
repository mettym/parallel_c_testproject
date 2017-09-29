#include "c_submodule.h"

int b=0;
void set_b(int value){
    b = value;
}
void inc_b(void){
    for(int i=0; i<1000; i++){
        b++;
        for(volatile int n=0; n<10000;n++);
    }
}
int get_b(void){
return b;
}
