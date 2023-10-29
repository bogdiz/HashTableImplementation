#include <math.h>

#include "prime.h"

int is_prime(const int n){
    if (n < 2)
        return 0;
    if (n % 2 == 0 && n != 2)
        return 0;
    for (int i = 3; i <= sqrt(n); i += 2)
        if (n % i == 0)
            return 0;
    return 1;
}

int next_prime(int n){
    while (!is_prime(n)){
        n++;
    }
    return n;
}