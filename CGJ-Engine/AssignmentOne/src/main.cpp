#include <iostream>
#include "../headers/Vector3.h"

int main() {
    Vector3 vec1(1,2,3);
    std::cout << "Vector 1: " << vec1 << "\n";

    Vector3 vec2;
    std::cout << "Vector 2: " << vec2 << "\n";

    return 0;
}