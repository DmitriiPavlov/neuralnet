//internal
#include <list>
//external
#include "matrix.h"

#ifndef NNPT20_LAYERS_H
#define NNPT20_LAYERS_H

template <typename T>
class Layer{
public:
    Matrix<T> weights;
    Matrix<T> zvector;
    Matrix<T> avector;
    Matrix<T> bvector;

    explicit Layer(int in, int out):
    weights(in,out), zvector(1,out), avector(1,out), bvector(1,out){};


    T& a(int i){
        assert(zvector.h == avector.h);
        return avector(i,0);
    }

    T& w(int i, int j) {
        return weights(j,i);
    }

    T& z(int i){
        return zvector(i,0);
    }

    T& b(int i){
        return bvector(i,0);
    }

    void fillRandom(){
        fillMatrixRandom(weights);
    }

    void zeroOut(){
        fillMatrixZeros(weights);
        fillMatrixZeros(bvector);
        fillMatrixZeros(avector);
        fillMatrixZeros(zvector);
    }

    Matrix<T>& apply(const Matrix<T>& in){
        matmul(weights,in,zvector);
        for (int i = 0; i < zvector.h; i++){
            z(i) += b(i);
        }
        for (int i = 0; i < zvector.h; i++){
            a(i) = ACTIVATION(z(i));
        }
        return avector;
    }

    //Currently using ReLu activation function
    T ACTIVATION(T num){
        if (num < 0){
            return 0.01*num;
        }
        return num;
    }
};

template <typename T>
class Network{
public:
    std::vector<Layer<T>> layers;
    Network(const std::vector<int>& layer_sizes){
        for (int i = 1; i < layer_sizes.size(); i++){
            layers.push_back(Layer<T>(layer_sizes[i-1],layer_sizes[i]));
        }
    };

    void zeroOut(){
        for (auto& layer:  layers){
            layer.zeroOut();
        }
    }
    Layer<double>& output(){
        return layers.back();
    }
    Layer<double>& layer(int i){
        return layers[i];
    }
    const Matrix<T>& apply(Matrix<T>& input){
        Matrix<T> curr = input;
        for (int i = 0; i < layers.size(); i++){
            curr = layers[i].apply(curr);
        }
        return layers.back().avector;
    }
};

#endif //NNPT20_LAYERS_H
