//
// Created by petko on 12/03/2021.
//

#include "factorial.h"

unsigned long long factorial(unsigned int n) {
    return (n<=1) ? 1 : n*factorial(n-1);
}