//internal
#include "matrix.h"
#include "layers.h"
#define IS_TRUE(x) { if (!(x)) std::cout << __FUNCTION__ << " failed on line " << __LINE__ << std::endl; }

//test
void testMatrixInitialization(){
    Matrix<double> a(3,4);
    a(2,2) = 5;
    a(0,0) = 1;
    IS_TRUE(a(0,1) == 0);
    IS_TRUE(a(2,2)==5);
    Matrix<double> b(12,1);
    b(0,11) = 2431.141;
    IS_TRUE(b(0,11) == 2431.141);
}

//test
void testMatrixPrint(){
    Matrix<double> b(12,1);
    b(0,11) = 2431.141;
    printMatrix(b);
    Matrix<double> a(10,21);
    a(10,5) = 2431.141;
    printMatrix(a);
}

//test
void testMatrixMultiplication(){
    Matrix<double> a(4,2);
    Matrix<double> b(2,4);
    Matrix<double> c(2,2);
    Matrix<double> test(2,2);
    test(0,0) = 12;
    test(0,1) = 36;
    test(1,0) = 35;
    test(1,1) = 95;

    a(0,1) = 1;
    a(0,2) = 3;
    a(1,2) = 1.5;
    a(0,3) = 6;
    a(1,3) = 7;

    b(3,1) = 5;
    b(3,0) = 2;
    b(1,1) = 6;
    b(0,0) = 7;
    b(0,1) = 8;

    matmul(a,b,c);
    IS_TRUE(areEqual(test,c))
}

void networkFunctionalityTest(){
    std::vector<int> layer_specs = {2,4,3,1};
    Network<double> network = Network<double>(layer_specs);

}