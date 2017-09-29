#include "c_module.h"

static int a=0;
void set_a(int value){
    a = value;
}
void inc_a(void){
    for(int i=0; i<1000; i++){
        a++;
        for(volatile int n=0; n<10000;n++);
    }
    /* using also a sub-module */
    set_b(a);
    inc_b();
    a = get_b();
}
int get_a(void){
    return a;
}
