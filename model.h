#include "layers.h"

class Model{

public:
    Network<double> network;
    Network<double> gradient;
    Network<double> batched_gradient;
    const double learning_rate = -0.001;
    const double batch_size = 100;
    double dCost = 0;
    Model(const std::vector<int>& sizes):
    network(sizes),gradient(sizes),batched_gradient(sizes)
    {
        for (Layer<double>& layer : network.layers){
            layer.fillRandom();
        }
    }

    const Matrix<double>& predict(Matrix<double>& input){
        return network.apply(input);
    }

    void adjustWeights(){
        addWeights(network,batched_gradient,learning_rate);
        batched_gradient.zeroOut();
    }

    void trainBatch(Matrix<double>& input, const Matrix<double>& correct_output){
        computeGradient(input,correct_output);
        addWeights(batched_gradient,gradient,1/batch_size);
    }
    static void addWeights(Network<double>& n1, Network<double>& n2, double magnitude_learning){
        for (int Lk = 0; Lk < n1.layers.size(); Lk++){
            Layer<double>& layr = n1.layer(Lk);
            Layer<double>& tlayr = n2.layer(Lk);
            for (int i = 0; i < layr.avector.h; i++) {
                layr.b(i) += magnitude_learning*tlayr.b(i);
            }
            for (int i = 0; i < layr.weights.h; i++) {
                for (int j = 0; j < layr.weights.w; j++) {
                    layr.w(j, i) += magnitude_learning * tlayr.w(j, i);
                }
            }

        }
    }

    void computeGradient(Matrix<double>& input, const Matrix<double>& correct_output){
        //first we want to fill in the output derivative
        network.apply(input);
        for (int i = 0; i < network.output().weights.h; i++){
            gradient.output().z(i) = 2*(network.output().
                    z(i)  - correct_output(i,0));
        }

        for (int Lk = network.layers.size()-1; Lk >= 0; Lk --){
            //we want to fill in the z, then the weights, and finally the a (of the previous layer)

            //first we fill in the z
            //remember dC/dzi = dC/dai if a>0 and 0 otherwise
            for (int i = 0; i < network.layer(Lk).avector.h; i++){
                //watch out here, i am essentially bypassing the last layer's ReLu
                if (network.layer(Lk).a(i) > 0 || Lk == network.layers.size()-1 ){
                    gradient.layer(Lk).z(i) = gradient.layer(Lk).a(i);
                }
                else{
                    gradient.layer(Lk).z(i) = 0.01*gradient.layer(Lk).a(i);
                    //leaky ^^^
                }
            }

            if (Lk > 0) {            //now we fill in the weights
                for (int i = 0; i < network.layer(Lk - 1).avector.h; i++) {
                    double sum = 0;
                    for (int j = 0; j < network.layer(Lk).avector.h; j++) {
                        gradient.layer(Lk).w(i, j) = network.layer(Lk - 1).a(i) * gradient.layer(Lk).z(j);
                        sum += network.layer(Lk).w(i,j)* gradient.layer(Lk).z(j);
                    }
                    gradient.layer(Lk - 1).a(i) = sum;
                }
            }
            else{
                for (int i = 0; i < input.h; i++) {
                    for (int j = 0; j < network.layer(Lk).avector.h; j++) {
                        gradient.layer(Lk).b(j) = gradient.layer(Lk).z(j);
                        gradient.layer(Lk).w(i, j) = input(i,0) * gradient.layer(Lk).z(j);
                    }
                }
            }
        }
    }

    double computeCost(const Matrix<double>& correct_output){
        double total = 0;
        for(int i = 0; i < correct_output.h; i++){
            total += (correct_output(i,0)-network.output().z(i))*(correct_output(i,0)-network.output().z(i));
        }
        return total;
    }

};