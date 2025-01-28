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

    explicit Layer(int in, int out):
    weights(in,out), zvector(1,out), avector(1,out){};

    Matrix<T>& apply(const Matrix<T>& in){
        matmul(weights,in,zvector);
        for (int i = 0; i < zvector.h; i++){
            avector(i,0) = ACTIVATION(zvector(i,0));
        }
        return avector;
    }
    T& a(int i){
        return avector(i,0);
    }

    T& w(int i, int j) {
        return weights(j,i);
    }

    //Currently using ReLu activation function
    T ACTIVATION(T num){
        if (num < 0){
            return 0;
        }
        return num;
    }
};

template <typename T>
class Network{
   std::vector<Layer<T>> layers;
public:
    Network(const std::vector<int>& layer_sizes){
        for (int i = 1; i < layer_sizes.size(); i++){
            layers.push_back(Layer<T>(layer_sizes[i-1],layer_sizes[i]));
        }
    };
    Layer<double>& layer(int i){
        return layers[i];
    }
    const Matrix<T>& apply(Matrix<T>& input){
        Matrix<T>& curr = input;
        for (int i = 0; i < layers.size(); i++){
            curr = layers[i].apply(curr);
        }
        return curr;
    }
};

#endif //NNPT20_LAYERS_H
