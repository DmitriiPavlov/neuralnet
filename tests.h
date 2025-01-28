//builtin
#include <random>
//internal
#include "matrix.h"
#include "layers.h"
#include "model.h"

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
    test(1,0) = 14;
    test(0,1) = 36;
    test(1,1) = 35;

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
    std::vector<int> layer_specs = {2,4,3};
    Network<double> network = Network<double>(layer_specs);
    network.layer(0).w(1,3) = 2;
    network.layer(0).w(0,2) = 4;
    network.layer(1).w(2,1) = 0.5;
    Matrix<double> input(1,2);
    input(0,0) = 1;
    network.apply(input);
    IS_TRUE(network.layer(1).a(1)==2);
    IS_TRUE(network.layer(0).a(2)==4);

}

void networkTrainingTest(){
//    std::vector<int> layers = {1,3,3,1};
//    Model mymodel(layers);
//    Matrix<double> input(1,1);
//    fillMatrixRandom(input);
//    Matrix<double> correct_output(1,1);
//
//    for (int i = 0; i < 2000; i++){
//        input(0,0) = generateRandomDouble(0,1);
//
//        correct_output(0,0) = input(0,0) * input(0,0);
//        mymodel.adjustWeights(input,correct_output);
//    }
//    input(0,0) = 0.2;
//    printMatrix(mymodel.predict(input));
//    input(0,0) = 0.3;
//    printMatrix(mymodel.predict(input));
//    input(0,0) = 0.4;
//    printMatrix(mymodel.predict(input));
//    input(0,0) = 0.5;
//    printMatrix(mymodel.predict(input));
    std::vector<int> layers = {1,1};
    Model mymodel(layers);
    Matrix<double> input(1,1);
    fillMatrixRandom(input);
    Matrix<double> correct_output(1,1);
    for (int i = 1; i < 2000; i++){
        if (i%100 == 0){
            mymodel.adjustWeights();
        }
        input(0,0) = generateRandomDouble(0.0,1.0);
        correct_output(0,0) = 0;
        mymodel.trainBatch(input,correct_output);
    }
    input(0,0) = 2.8;
    printMatrix(mymodel.predict(input));
    input(0,0) = 1.0;
    printMatrix(mymodel.predict(input));
    input(0,0) = 0.5;
    printMatrix(mymodel.predict(input));
    input(0,0) =0.01;
    printMatrix(mymodel.predict(input));
}