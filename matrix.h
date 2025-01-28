//builtin
#include <list>
#include <random>
#ifdef MATRIX_H
#else
#define MATRIX_H

#include <cstdio>
#include <cassert>

template <typename T>
class Matrix{
public:
    int w{}, h{};
    std::vector<T> m_data;
    //for those who don't remeber linalg (me), the width is the size of the input, the height
    //is the size of the output
    Matrix(int pw, int ph) {
        this->w = pw;
        this->h = ph;
        m_data.resize(pw * ph);
    }
    double& operator()(int row, int col)
    {

        assert(row >= 0 && row < h);
        assert(col >= 0 && col < w);

        return m_data[row * w + col];
    }

    double operator()(int row, int col) const
    {
        assert(row >= 0 && row < h);
        assert(col >= 0 && col < w);

        return m_data[row * w + col];
    }
    ~Matrix(){
    }

};

double generateRandomDouble(double min, double max) {
    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_real_distribution<> dis(min, max);

    return dis(gen);
}

template <typename T>void matmul(const Matrix<T>& A, const Matrix<T>& B, Matrix<T>& C) {
    assert(A.w == B.h);
    assert(C.h == A.h && C.w == B.w);

    for (int i = 0; i < A.h; i++) {
        for (int j = 0; j < B.w; j++) {
            C(i, j) = 0;
            for (int k =0; k < A.w; k++) {
                C(i, j) += A(i, k) * B(k, j);
            }
        }
    }
}
template <typename T>
void printMatrix(const Matrix<T>& mat) {
    const int w = 10;
    const int precision = 2;
    for (int i = 0; i < mat.h; i++) {
        for (int j = 0; j < mat.w; j++) {
            std::printf("%-*.*f ", w, precision, mat(i, j));
        }
        std::printf("\n");
    }
    std::cout<<"\n";
}

void fillMatrixRandom(Matrix<double>& m){
    for (int i = 0; i < m.w; i++){
        for (int j = 0; j < m.h; j++){
            m(j,i) = generateRandomDouble(0.3,0.5);
        }
    }
}
void fillMatrixZeros(Matrix<double>& m){
    for (int i = 0; i < m.w; i++){
        for (int j = 0; j < m.h; j++){
            m(j,i) = 0;
        }
    }
}
template <typename T>
bool areEqual(const Matrix<T>& a, const Matrix<T>& b){
    if (a.w != b.w || a.h != b.h){
        std::cout<<"here";
        return false;
    }
    for (int i = 0; i < a.w; i++){
        for (int j = 0; j < a.h; j++){
            if (a(j,i) != b(j,i)){
                std::cout<<"here";
                return false;
            }
        }
    }
    return true;
}
#endif
