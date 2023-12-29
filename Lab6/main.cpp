#include <iostream>
#include <fstream>

const double eps = 1E-6;


double pow(double a, double n){
    double result = 1;
    int i = 0;
    while (i < n){
        result *= a;
        i++;
    }
    return result;
}



double* Gauss(double **a, double *y, int n){
    double *x, max;
    int k, index;
    x = new double[n];
    k = 0;
    while (k < n){
        max = std::abs(a[k][k]);
        index = k;
        for (int i = k + 1; i < n; i++){
            if (std::abs(a[i][k]) > max){
                max = std::abs(a[i][k]);
                index = i;
            }
        }

        if (max < eps){
            return nullptr;
        }
        for (int j = 0; j < n; j++){
            double temp = a[k][j];
            a[k][j] = a[index][j];
            a[index][j] = temp;
        }
        double temp = y[k];
        y[k] = y[index];
        y[index] = temp;


        for (int i = k; i < n; i++){
            double temporary = a[i][k];
            if (std::abs(temporary) < eps)
                continue;
            for (int j = 0; j < n; j++)
                a[i][j] = a[i][j] / temporary;
            y[i] = y[i] / temporary;



            if (i == k)
                continue;
            for (int j = 0; j < n; j++)
                a[i][j] = a[i][j] - a[k][j];
            y[i] = y[i] - y[k];
        }
        k++;
    }



    for (k = n - 1; k >= 0; k--){
        x[k] = y[k];
        for (int i = 0; i < k; i++)
            y[i] = y[i] - a[i][k] * x[k];
    }


    return x;
}


double** newMatrixNorm(double **a, double*& y, int n){
    auto* yret = new double[n];
    auto** aret = new double*[n];

    aret[0] = new double[n];


    //std::cout << a[0][0];



    aret[0][0] = n;
    aret[0][1] = a[0][0] + a[1][0] + a[2][0] + a[3][0] + a[4][0] + a[5][0];
    aret[0][2] = a[0][1] + a[1][1] + a[2][1] + a[3][1] + a[4][1] + a[5][1];
    aret[0][3] = a[0][2] + a[1][2] + a[2][2] + a[3][2] + a[4][2] + a[5][2];
    aret[0][4] = a[0][3] + a[1][3] + a[2][3] + a[3][3] + a[4][3] + a[5][3];
    aret[0][5] = a[0][4] + a[1][4] + a[2][4] + a[3][4] + a[4][4] + a[5][4];

    y[0] = a[0][5] + a[1][5] + a[2][5] + a[3][5] + a[4][5] + a[5][5];
    aret[1] = new double[n];


    aret[1][0] = aret[0][1];
    aret[1][1] = (a[0][0] * a[1][0] * a[2][0] * a[3][0] * a[4][0] * a[5][0]) + (a[0][0] * a[1][0] * a[2][0] * a[3][0] * a[4][0] * a[5][0]);
    aret[1][2] = (a[0][0] * a[1][0] * a[2][0] * a[3][0] * a[4][0] * a[5][0]) + (a[0][1] * a[1][1] * a[2][1] * a[3][1] * a[4][1] * a[5][1]);
    aret[1][3] = (a[0][0] * a[1][0] * a[2][0] * a[3][0] * a[4][0] * a[5][0]) + (a[0][2] * a[1][2] * a[2][2] * a[3][2] * a[4][2] * a[5][2]);
    aret[1][4] = (a[0][0] * a[1][0] * a[2][0] * a[3][0] * a[4][0] * a[5][0]) + (a[0][3] * a[1][3] * a[2][3] * a[3][3] * a[4][3] * a[5][3]);
    aret[1][5] = (a[0][0] * a[1][0] * a[2][0] * a[3][0] * a[4][0] * a[5][0]) + (a[0][4] * a[1][4] * a[2][4] * a[3][4] * a[4][4] * a[5][4]);

    y[1] = (a[0][5] * a[1][5] * a[2][5] * a[3][5] * a[4][5] * a[5][5]) + (a[0][0] * a[1][0] * a[2][0] * a[3][0] * a[4][0] * a[5][0]);
    aret[2] = new double[n];

    aret[2][0] = aret[0][2];
    aret[1][1] = (a[0][1] * a[1][1] * a[2][1] * a[3][1] * a[4][1] * a[5][1]) + (a[0][0] * a[1][0] * a[2][0] * a[3][0] * a[4][0] * a[5][0]);
    aret[1][2] = (a[0][1] * a[1][1] * a[2][1] * a[3][1] * a[4][1] * a[5][1]) + (a[0][1] * a[1][1] * a[2][1] * a[3][1] * a[4][1] * a[5][1]);
    aret[1][3] = (a[0][1] * a[1][1] * a[2][1] * a[3][1] * a[4][1] * a[5][1]) + (a[0][2] * a[1][2] * a[2][2] * a[3][2] * a[4][2] * a[5][2]);
    aret[1][4] = (a[0][1] * a[1][1] * a[2][1] * a[3][1] * a[4][1] * a[5][1]) + (a[0][3] * a[1][3] * a[2][3] * a[3][3] * a[4][3] * a[5][3]);
    aret[1][5] = (a[0][1] * a[1][1] * a[2][1] * a[3][1] * a[4][1] * a[5][1]) + (a[0][4] * a[1][4] * a[2][4] * a[3][4] * a[4][4] * a[5][4]);

    y[2] = (a[0][5] * a[1][5] * a[2][5] * a[3][5] * a[4][5] * a[5][5]) + (a[0][1] * a[1][1] * a[2][1] * a[3][1] * a[4][1] * a[5][1]);
    aret[3] = new double[n];

    aret[3][0] = aret[0][3];
    aret[3][1] = (a[0][2] * a[1][2] * a[2][2] * a[3][2] * a[4][2] * a[5][2]) + (a[0][0] * a[1][0] * a[2][0] * a[3][0] * a[4][0] * a[5][0]);
    aret[3][2] = (a[0][2] * a[1][2] * a[2][2] * a[3][2] * a[4][2] * a[5][2]) + (a[0][1] * a[1][1] * a[2][1] * a[3][1] * a[4][1] * a[5][1]);
    aret[3][3] = (a[0][2] * a[1][2] * a[2][2] * a[3][2] * a[4][2] * a[5][2]) + (a[0][2] * a[1][2] * a[2][2] * a[3][2] * a[4][2] * a[5][2]);
    aret[3][4] = (a[0][2] * a[1][2] * a[2][2] * a[3][2] * a[4][2] * a[5][2]) + (a[0][3] * a[1][3] * a[2][3] * a[3][3] * a[4][3] * a[5][3]);
    aret[3][5] = (a[0][2] * a[1][2] * a[2][2] * a[3][2] * a[4][2] * a[5][2]) + (a[0][4] * a[1][4] * a[2][4] * a[3][4] * a[4][4] * a[5][4]);

    y[3] = (a[0][5] * a[1][5] * a[2][5] * a[3][5] * a[4][5] * a[5][5]) + (a[0][2] * a[1][2] * a[2][2] * a[3][2] * a[4][2] * a[5][2]);
    aret[4] = new double[n];

    aret[4][0] = aret[0][4];
    aret[4][1] = (a[0][3] * a[1][3] * a[2][3] * a[3][3] * a[4][3] * a[5][3]) + (a[0][0] * a[1][0] * a[2][0] * a[3][0] * a[4][0] * a[5][0]);
    aret[4][2] = (a[0][3] * a[1][3] * a[2][3] * a[3][3] * a[4][3] * a[5][3]) + (a[0][1] * a[1][1] * a[2][1] * a[3][1] * a[4][1] * a[5][1]);
    aret[4][3] = (a[0][3] * a[1][3] * a[2][3] * a[3][3] * a[4][3] * a[5][3]) + (a[0][2] * a[1][2] * a[2][2] * a[3][2] * a[4][2] * a[5][2]);
    aret[4][4] = (a[0][3] * a[1][3] * a[2][3] * a[3][3] * a[4][3] * a[5][3]) + (a[0][3] * a[1][3] * a[2][3] * a[3][3] * a[4][3] * a[5][3]);
    aret[4][5] = (a[0][3] * a[1][3] * a[2][3] * a[3][3] * a[4][3] * a[5][3]) + (a[0][4] * a[1][4] * a[2][4] * a[3][4] * a[4][4] * a[5][4]);

    y[4] = (a[0][5] * a[1][5] * a[2][5] * a[3][5] * a[4][5] * a[5][5]) + (a[0][3] * a[1][3] * a[2][3] * a[3][3] * a[4][3] * a[5][3]);
    aret[5] = new double[n];

    aret[5][0] = aret[0][5];
    aret[5][1] = (a[0][4] * a[1][4] * a[2][4] * a[3][4] * a[4][4] * a[5][4]) + (a[0][0] * a[1][0] * a[2][0] * a[3][0] * a[4][0] * a[5][0]);
    aret[5][2] = (a[0][4] * a[1][4] * a[2][4] * a[3][4] * a[4][4] * a[5][4]) + (a[0][1] * a[1][1] * a[2][1] * a[3][1] * a[4][1] * a[5][1]);
    aret[5][3] = (a[0][4] * a[1][4] * a[2][4] * a[3][4] * a[4][4] * a[5][4]) + (a[0][2] * a[1][2] * a[2][2] * a[3][2] * a[4][2] * a[5][2]);
    aret[5][4] = (a[0][4] * a[1][4] * a[2][4] * a[3][4] * a[4][4] * a[5][4]) + (a[0][3] * a[1][3] * a[2][3] * a[3][3] * a[4][3] * a[5][3]);
    aret[5][5] = (a[0][4] * a[1][4] * a[2][4] * a[3][4] * a[4][4] * a[5][4]) + (a[0][4] * a[1][4] * a[2][4] * a[3][4] * a[4][4] * a[5][4]);

    y[5] = (a[0][5] * a[1][5] * a[2][5] * a[3][5] * a[4][5] * a[5][5]) + (a[0][4] * a[1][4] * a[2][4] * a[3][4] * a[4][4] * a[5][4]);

    //std::cout << y[0] << " " << y[1] << " " << y[2] << " " << y[3] << " " << y[4] << " " << y[5];



    return aret;

}


double** newMatrix(int n, double*& y){
    std::ifstream filematrix("matrix.txt");
    auto** an = new double*[n];
    for(int i = 0; i < n; i++){
        an[i] = new double[n];
        for(int j = 0; j <= n; j++){
            if(j != 6)
                filematrix >> an[i][j];
            else
                filematrix >> y[i];

        }
    }
    filematrix.close();
    return an;
}


double* square(double* x_arr, const double* y_arr){
    auto* res = new double[2];
    double xy = 0;
    double x2 = 0;
    double sumx = 0;
    double sumy = 0;
    for(int i = 0; i < 4; i++) {
        sumx += x_arr[i];
        sumy += y_arr[i];
    }


    for(int i = 0; i < 4; i++){
        xy += x_arr[i] * y_arr[i];
        x2 += pow(x_arr[i], 2);
    }

    double a = (4 * xy - sumx * sumy) / (4 * x2  - pow(sumx, 2));
    double b = (sumy - a * sumx) / 4;

    res[0] = a;
    res[1] = b;


    return res;
}


double Lagranj(const double* x_arr, const double* y_arr, double x){
    double L = 0;
    for(int i = 0; i < 4; i++){
        double temp = y_arr[i];
        for(int j = 0; j < 4; j++){
            if( i != j){
                temp *= (x - x_arr[j]) / (x_arr[i] - x_arr[j]);
            }
        }
        L += temp;
    }
    return L;
}


int main() {
    double **a, *y, *x;
    int n;
    std::ifstream input("input.txt");
    input >> n;
    a = new double* [n];
    y = new double[n];
    for(int i = 0; i < n; i++){
        a[i] = new double[n];
        for(int j = 0; j <= n; j++){
            if(j != 5)
                input >> a[i][j];
            else
                input >> y[i];
        }
    }
    input.close();

    double** aa = newMatrix(n, y);

    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            if(j != 5)
                std::cout << aa[i][j] << " ";
            else
                std::cout << aa[i][j] << "\n";

    for(int i = 0; i < n; i++)
        std::cout << y[i] << " ";


    x = Gauss(aa, y, n);

    std::cout << "\n\n";

    for(int i = 0; i < n; i++)
        std::cout << x[i] << " ";

    auto* M = new double[n];
    M[0] = 2;
    M[1] = 4;
    M[2] = 6;
    M[3] = 9;
    M[4] = 12;
    M[5] = 11;

    auto* xarr = new double[4];
    auto* yarr = new double[4];

    xarr[0] = 2;
    xarr[1] = 4;
    xarr[2] = 8;
    xarr[3] = 12;

    yarr[0] = 1;
    yarr[1] = 4;
    yarr[2] = 12;
    yarr[3] = 17;

    std::cout << "\n\n";

    double* ans2 = square(xarr, yarr);

    for(int i = 0; i < 2; i++)
        std::cout << ans2[i] << " ";




    double L = Lagranj(xarr, yarr, 5);

    std::cout << "\n\n" << L;


    return 0;
}
