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
    weights(in,out), zvector(out,1), avector(out,1){};

    const Matrix<T>& apply(const Matrix<T>& in){
        matmul(weights,in,zvector);
        for (int i = 0; i < zvector.h; i++){
            avector(i,1) = ACTIVATION(zvector(i,1));
        }
    }

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
    T& a(int L, int i){
        return layers[L].avector(i,1);
    }
    T& z(int L, int i){
        return layers[L].zvector(i,1);
    }

    T& w(int L, int i, int j){
        return layers[L].weights(i,j);
    }

    const Matrix<T>& apply(const Matrix<T>& input){
        Matrix<T>& curr = input;
        for (int i = 0; i < layers.size(); i++){
            curr = layers[i].apply(curr);
        }
        return curr;
    }
};

#endif //NNPT20_LAYERS_H
