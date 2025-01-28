#include "layers.h"

class Model{

public:
    Network<double> network;
    Network<double> gradient;
    Matrix<double>  input;
    Model(const std::vector<int>& sizes):
    network(sizes),gradient(sizes),input(1,sizes[0])
    {

    }

    const Matrix<double>& predict(Matrix<double>& input){
        return network.apply(input);
    }

    void adjustWeights(const Matrix<double>& input, const Matrix<double>& correct_output){

    }

    void computeGradient(Matrix<double>& input, const Matrix<double>& correct_output){
        //first we want to fill in the output derivative
        network.apply(input);

        for (int i = 0; i < network.output().weights.h; i++){
            gradient.output().a(0) = 2*(network.output().a(0)  - correct_output(0,0));
        }

        for (int Lk = network.layers.size()-1; Lk >= 0; Lk --){
            //we want to fill in the z, then the weights, and finally the a (of the previous layer)

            //first we fill in the z
            //remember dC/dzi = dC/dai if a>0 and 0 otherwise
            for (int i = 0; i < network.layer(Lk).avector.h; i++){
                if (network.layer(Lk).a(i) > 0){
                    gradient.layer(Lk).z(i) = gradient.layer(Lk).a(i);
                }
                else{
                    gradient.layer(Lk).z(i) = 0;
                }
            }

            if (Lk > 0) {            //now we fill in the weights
                for (int i = 0; i < network.layer(Lk - 1).avector.h; i++) {
                    double sum = 0;
                    for (int j = 0; j < network.layer(Lk).avector.h; j++) {
                        gradient.layer(Lk).w(i, j) = network.layer(Lk - 1).a(i) * gradient.layer(Lk).z(j);
                        sum += network.layer(Lk).weights(i, j) * gradient.layer(Lk).z(j);
                    }
                    gradient.layer(Lk - 1).a(i) = sum;
                }
            }
            else{
                for (int i = 0; i < input.h; i++) {
                    for (int j = 0; j < network.layer(Lk).avector.h; j++) {
                        gradient.layer(Lk).w(i, j) = input(i,0) * gradient.layer(Lk).z(j);
                    }
                }
            }
        }
    }

};