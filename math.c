#include"math.h"

//Calculates square root of x using newtons method
float square_root(float s){
    //Starting guess
    float x = 1;
    while(x*x < s) x++;
    int i;
    for(i = 0; i < 50; i++) {
        x = x - ((x*x - s)/(2*x));
    }
    if(x < 0) return -1*x;
    return x;
}

float power(float x, float y){
    int i;
    for(i = 1; i < y; i++){
        x *= x;
    }
    return x;
}