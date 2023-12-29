#include <iostream>
#include <fstream>
#include "matrix.h"
using namespace std;

const double eps = 1E-7;


class SLAU : public matrix{
public:

    SLAU(double *res, int line);

    double* Method_of_Kramer() const;

};

SLAU::SLAU(double *res, int line) : matrix(res, line, line+1){
}

double* SLAU:: Method_of_Kramer() const{
    auto *result = new double[line];
    if(line != column - 1){
        for(int i = 0; i < line; i++){
            result[i] = 0;
        }
        return result;
    }
    matrix slau(line, line);
    for(int i = 0; i < line; i++){
        for(int j = 0; j < line; j++)
            slau(i, j) = Matrix[i][j];
    }
    double determinant = slau.Determinant();
    if(determinant == 0){
        result[0] = result[1] = result[2] = strtod("39909!", nullptr); //error :)
        return result;
    }
    for(int i = 0; i < line; i++){
        if(i > 0)
            for(int j = 0; j < line; j++)
                slau(j, i - 1) = Matrix[j][i - 1];
        for(int j = 0; j < line; j++)
            slau(j, i) = Matrix[j][line];
        result[i] = slau.Determinant() / determinant;
    }
    return result;
}




void MatrixPrint(double **a, double *y, int n){
    cout << "\nThere is our matrix: \n";
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++) {
            if (a[i][j] >= 0) {
                cout << a[i][j] << "x" << j + 1;
                if (j < n - 1)
                    cout << " + ";
            }
            else{
                cout << "(" << a[i][j] << "x" << j + 1 << ")";
                if (j < n - 1)
                    cout << " + ";
            }
        }
        cout << " = " << y[i] << endl;
    }
}


double* Gauss(double **a, double *y, int n){
    double *x, max;
    int k, index;
    x = new double[n];
    k = 0;
    while (k < n){
        max = abs(a[k][k]);
        index = k;
        for (int i = k + 1; i < n; i++){
            if (abs(a[i][k]) > max){
                max = abs(a[i][k]);
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
            if (abs(temporary) < eps)
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



double* itermethod(double** a, const double* y, int n){

    auto* res = new double[n];
    auto* Xn = new double[n];

    do{
        for(int i = 0; i < n; i++){
            Xn[i] = y[i] / a[i][i];
            for(int j = 0; j < n; j++){
                if(i == j)
                    continue;
                else
                    Xn[i] -= a[i][j] / a[i][i] * res[j];
            }
        }
        bool flag = true;
        for(int i = 0; i < n - 1; i++){
            if(abs(Xn[i] - res[i]) > eps){
                flag = false;
                break;
            }
        }

        for(int i = 0; i < n; i++)
            res[i] = Xn[i];

        if(flag)
            break;

    } while(true);

    return res;

}



int main(){
    double **a, *y, *x;
    int n;
    ifstream input("input.txt");
    input >> n;
    cout << "\nCount of Uravneniyas = " << n << endl;
    for(int i = 0; i < 48; i++)
        cout << char(2500);
    cout << "\nGreat! There are our coefficients" << "\t\t" << char(2502) << "\n";
    a = new double* [n];
    y = new double[n];
    for (int i = 0; i < n; i++){
        a[i] = new double[n];
        for (int j = 0; j < n; j++){
            input >> a[i][j];
            cout << "a[" << i << "][" << j << "]= " << a[i][j] << "\t\t\t\t\t" << char(2502) << endl;
        }
    }
    for(int i = 0; i < 48; i++)
        cout << char(2500);

    cout << "\nThat's it! There are answers of our system:" << "\t" << char(2502) << endl;
    for(int i = 0; i < n; i++){
        input >> y[i];
        if(y[i] < 0){
            cout << "y[" << i << "]= " << y[i] << "\t\t\t\t\t" << char(2502) << endl;
        }
        else{
            cout << "y[" << i << "]= " << y[i] << "\t\t\t\t\t\t" << char(2502) << endl;
        }
    }
    input.close();
    for(int i = 0; i < 48; i++)
        cout << char(2500);
    cout << endl;
    MatrixPrint(a, y, n);
    x = Gauss(a, y, n);
    if (x == nullptr){
        cout << "Error!";
        return 0;
    }
    cout << endl;
    for(int i = 0; i < 48; i++)
        cout << char(2500);
    cout << endl;
    cout << "There are our answers!\t\t\t\t" << char(2502) << "\n";
    for (int i = 0; i < n; i++)
        cout << "x[" << i << "]= " << x[i] << "\t\t\t\t\t" << char(2502) << endl;
    for(int i = 0; i < 48; i++)
        cout << char(2500);


    for (int i = 0; i < n; i++)
        delete[] a[i];

    delete[] a;
    delete[] x;
    delete[] y;




    ifstream filein("input3.txt");
    filein >> n;
    y = new double[n];
    a = new double*[n];
    for(int i = 0; i < n; i++)
        a[i] = new double[n];

    for(int i = 0; i < n; i++){
        for(int j = 0; j <= n; j++){
            if(j != n)
                filein >> a[i][j];
            else
                filein >> y[i];
        }
    }
    filein.close();
    cout << "\n";
    for(int i = 0; i < n; i++){
        for(int j = 0; j <= n; j++){
            if(j != n)
                cout << a[i][j] << " ";
            else
                cout << y[i] << "\n";
        }
    }

    x = itermethod(a, y, n);

    cout << "\n\n";

    for(int i = 0; i < n; i++)
        cout << x[i] << " ";

    cout << "\n";

    return 0;
}