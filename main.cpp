#include "array.h"
#include <iostream>

using namespace std;

int main() {
    LouiseArray<int> numbers;
    for(int i = 0; i < (1 << 26); i++) {
        numbers.push(5);
    }
    for(int i = 0; i < 100'000'000; i++) {
        numbers.push(5);
        numbers.pop();
    }
    return 0;
}
