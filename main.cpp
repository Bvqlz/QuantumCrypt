#include <iostream>
#include "src/chunk.h"

int main()
{
    Quantum q(128), q2(64);
    std::cout << "Modulo 128 Cypher: " << std::endl;
    q.cypher();
    std::cout << "Modulo 64 Cypher: " << std::endl;
    q2.cypher();
}

