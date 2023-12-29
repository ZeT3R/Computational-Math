#include <iostream>
#include <cmath>
#include <iomanip>
const double eps = 1E-6;
double Err = 0;


double* MakeMatrixSterjenTest(double**& temp, int I, double* line){
    double h = 0.1;
    int M = 11;
    double a = 2.3 * 0.00001;
    double ht = 600000;

    for(int j = 1; j < M - 1; j++){
        line[j] = temp[I-1][j] + (a * a * ht / (h * h)) * (temp[I-1][j+1] - 2 * temp[I-1][j] + temp[I-1][j-1]);
//        std::cout << std::setprecision(5) << line[j] << " ";
    }
//    std::cout << "\n";
    return line;
}


void MakeMatrixSterjen(double**& temp, int N){
    double h = 0.1;
    temp[0][0] = sin(M_PI * 0);
    int M = 11;
    double a = 2.3 * 0.00001;
    double ht = 600000;
    for(int i = 0; i < N; i++)
        for (int j = 0; j < M; j++) {
            if (j == 0 || j == M - 1) {
                temp[i][j] = temp[0][0];
            }
        }

    for(int j = 1; j < M - 1; j++){
        temp[0][j] = sin(M_PI * (h * j));
    }

    for(int i = 1; i < N; i++){
        for(int j = 1; j < M - 1; j++){
            temp[i][j] = temp[i-1][j] + (a * a * ht / (h * h)) * (temp[i-1][j+1] - 2 * temp[i-1][j] + temp[i-1][j-1]);
        }
    }
}


void MakeMatrixPlastina(double**& temp, int N){
    int M = N;
    double dx = 1. / (N - 1), dy = 1. / (M - 1);
    double dt;

    if(dx < dy){
        dt = dx * dx / 2;
    }
    else{
        dt = dy * dy / 2;
    }

    dt *= 0.9;

    do{
        Err = 0;
        for(int i = 1; i < N - 1; i++){
            for(int j = 1; j < M - 1; j++){
                double T1 = temp[i][j] + dt * ((temp[i + 1][j] - 2 * temp[i][j] + temp[i - 1][j]) / pow(dx, 2) +
                        (temp[i][j + 1] - 2 * temp[i][j] + temp[i][j - 1]) / pow(dy, 2));

                Err += std::abs(T1 - temp[i][j]) / dt;
                temp[i][j] = T1;
            }
        }
    }while(Err > eps);
}


int main() {
    int N = 100;
    int M = 11;
    auto** matrix = new double*[N];

    for(int i = 0; i < N; i++){
        matrix[i] = new double[M];
        for(int j = 0; j < M; j++){
            if(j == 0 || j == M - 1)
                matrix[i][j] = sin(M_PI * 0);
            else matrix[i][j] = 0.;
        }
    }


    auto* line = new double[M];
    for(int i = 0; i < M; i++){
        if(i == 0 || i == M - 1)
            line[i] = sin(M_PI * 0);
        else
            line[i] = 0;
    }

    MakeMatrixSterjen(matrix, N);

    for(int k = 1; k < N; k++) {

        line = MakeMatrixSterjenTest(matrix, k, line);
        for(int i = 0; i < M; i++){
            std::cout << std::setprecision(5) << line[i] << " ";
        }
        std::cout << std::setprecision(5) << "\n";
    }


    int N2 = 21;
    auto** matrix2 = new double*[N2];

    for(int i = 0; i < N2; i++){
        matrix2[i] = new double[N2];
        for(int j = 0; j < N2; j++){
            if(j == 0 || j == N2 - 1)
                matrix2[i][j] = 1.;
            else matrix2[i][j] = 0.;
        }
    }



    MakeMatrixPlastina(matrix2, N2);

    //MakeMatrixSterjen(matrix, N);


    for(int i = 0; i < N; i++) {
        std::cout << "\n";
        for (int j = 0; j < M; j++)
            std::cout << std::setprecision(5) << matrix[i][j] << " ";
    }

    std::cout << "\n\n\n";

    for(int i = 0; i < N2; i++){
        for(int j = 0; j < N2; j++){
            std::cout << matrix2[i][j] << " ";
        }
        std::cout << "\n";
    }

    return 0;
}
