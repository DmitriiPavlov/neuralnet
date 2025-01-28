//builtin
#include <iostream>
//internal
#include "matrix.h"
#include "tests.h"

int main() {
    testMatrixInitialization();
    testMatrixPrint();
    testMatrixMultiplication();
    networkFunctionalityTest();
    networkTrainingTest();
    return 0;
}


