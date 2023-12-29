#include "matrix.h"

matrix::matrix(int k, int l){
    line = k;
    column = l;
    Matrix = new double*[k];
    for(int i = 0; i < k; i++){
        Matrix[i] = new double[l];
        }
}


matrix::matrix(double MMatrix, int k, int l){
    line = k;
    column = l;
    Matrix = new double*[line];
    for(int i = 0; i < k; i++){
        Matrix[i] = new double[k];
        for(int j = 0; j < l; j++){
            Matrix[i][j] = MMatrix;
        }
    }
}


matrix::matrix(const double *MMatrix, int k, int l){
    line = k;
    column = l;
    Matrix = new double*[line];
    for(int i = 0; i < k; i++){
        Matrix[i] = new double[l];
        for(int j = 0; j < l; j++)
            Matrix[i][j] = MMatrix[i * l + j];
    }
}


matrix::matrix(double **MMatrix, int k, int l){
    line = k;
    column = l;
    Matrix = new double*[line];
    for(int i = 0; i < k; i++){
        Matrix[i] = new double[l];
        for(int j = 0; j < l; j++){
            Matrix[i][j] = MMatrix[i][j];
        }
    }
}


matrix::matrix(const matrix& other){
    line = other.line;
    column = other.column;
    Matrix = new double*[line];
    for(int i = 0; i < line; i++){
        Matrix[i] = new double[column];
        for(int j = 0; j < column; j++){
            Matrix[i][j] = other.Matrix[i][j];
        }
    }
}


matrix::~matrix(){
    for(int i = 0; i < line; i++){
        delete[]Matrix[i];
    }
    delete[]Matrix;
}


matrix matrix::find_minor(int fbegin, int fend, int sbegin, int send) const{
    if((fbegin > fend) || (sbegin > send) || (fbegin < 0) || (sbegin < 0) || (fend > line - 1) || (send > column - 1)
    || ((fend - fbegin + 1) == line) || ((send - sbegin + 1) == column)){
        return *this;
    }

    matrix result(line - (fend - fbegin + 1), column - (send - sbegin + 1));
    for(int i = 0, lineminor = 0; i < line; i++){
        if((i >= fbegin) && (i <= fend)){
            continue;
        }
        for(int j = 0, columnminor = 0; j < column; j++){
            if((j >= sbegin) && (j <= send)){
                continue;
            }
            result.Matrix[lineminor][columnminor] = Matrix[i][j];
            ++columnminor;
        }
        ++lineminor;
    }
    return result;
}


double matrix::Determinant() const{
    if(line != column){
        return 0;
    }
    if(line == 1){
        return Matrix[0][0];
    }
    else if(line == 2){
        return ((Matrix[0][0] * Matrix[1][1]) - (Matrix[1][0] * Matrix[0][1]));
    }
    else {
        double determinant = 0;
        matrix add_matrix(line - 1, line - 1);
        for (int i = 0; i < line; i++) {
            add_matrix = find_minor(0, 0, i, i);
            determinant += (i % 2 ? -1 : 1) * Matrix[0][i] * add_matrix.Determinant();
        }
        return determinant;
    }
}


matrix matrix::Transpose() const{
    matrix Trans(column, line);
    for(int i = 0; i < line; i++){
        for(int j = 0; j < column; j++){
            Trans.Matrix[j][i] = Matrix[i][j];
        }
    }
    return Trans;
}


bool matrix::my_pow(double degree) {
    double res = -1.0;
    for(int k = 0; k < degree; k++){
        res *= -1.0;
    }
    return res < 0;
}


matrix matrix::invert()const{
    if(line != column){
        return *this;
    }
    if(Determinant() == 0){
        return *this;
    }
    matrix result(line, column);
    for(int i = 0; i < line; i++){
        for(int j = 0; j < column; j++){
            result.Matrix[i][j] = find_minor(i, i, j, j).Determinant();
            if(my_pow(i + j + 1.0)){
                result.Matrix[i][j] = -result.Matrix[i][j];
            }
        }
    }
    result = result.Transpose();
    result = (1 / Determinant()) * result;
    return result;
}


double& matrix::operator()(int ind1, int ind2){
    return Matrix[ind1][ind2];
}


double matrix::at(int ind1, int ind2){
    return Matrix[ind1][ind2];
}


double* matrix::operator[](int ind){
    return Matrix[ind];
}


std::ostream& operator <<(std::ostream& out, const matrix& MMatrix){
    for(int i = 0; i < MMatrix.line; i++){
        for(int j = 0; j < MMatrix.column; j++){
            out << MMatrix.Matrix[i][j] << " ";
        }
        out << '\n';
    }
    return out;
}


matrix operator*(const double &a, const matrix& b){
    return b * a;
}


matrix operator*(const matrix &a, const double &b){
    matrix result(a);
    for(int i = 0; i < result.line; i++)
        for (int j = 0; j < result.column; j++)
            result.Matrix[i][j] *= b;
    return result;
}


matrix operator*(const matrix &a, const matrix &b){
    matrix result(0.0, a.line, b.column);
    if(a.line != b.column){
        return result;
    }
    for(int i = 0; i < result.line; i++) {
        for (int j = 0; j < result.column; j++) {
            double sum = 0;
            for (int k = 0; k < a.column; k++) {
                sum += a.Matrix[i][k] * b.Matrix[k][j];
            }
            result.Matrix[i][j] = sum;
        }
    }
    return result;
}


matrix operator +(const matrix &a, const matrix &b){
    matrix result(0.0, a.line, a.column);
    if((a.line != b.line) || (a.column != b.column)){
        return result;
    }
    for(int i = 0; i < result.line; i++){
        for(int j = 0; j < result.column; j++){
            result.Matrix[i][j] = a.Matrix[i][j] + b.Matrix[i][j];
        }
    }
    return result;
}


matrix operator -(const matrix &a){
    matrix result(a);
    for(int i = 0; i < a.line; i++){
        for(int j = 0; j < a.column; j++){
            result.Matrix[i][j] = -a.Matrix[i][j];
        }
    }
    return result;
}


matrix operator -(const matrix &a, const matrix &b){
    return a + (-b);
}


matrix operator +(const matrix &a){
    matrix result(a);
    for(int i = 0; i < a.line; i++){
        for(int j = 0; j < a.column; j++){
            if(result.Matrix[i][j] < 0) {
                result.Matrix[i][j] = -a.Matrix[i][j];
            }
        }
    }
    return result;
}


matrix operator /(const matrix &a, const matrix &b){
    if(b.Determinant() == 0){
        return a;
    }
    return a * b.invert();
}


matrix operator /(const double &a, const matrix &b){
    return b.invert() * a;
}


matrix operator /(const matrix &a, const double &b){
    return a * (1 / b);
}


matrix& matrix::operator =(const matrix &a){
    if(this == &a){
        return *this;
    }
    for(int i = 0; i < line; i++){
        delete[] Matrix[i];
    }
    delete[] Matrix;
    line = a.line;
    column = a.column;
    Matrix = new double*[line];
    for(int i = 0; i < line; i++){
        Matrix[i] = new double[column];
        for(int j = 0; j < column; j++){
            Matrix[i][j] = a.Matrix[i][j];
        }
    }
    return *this;
}


matrix& matrix:: operator +=(const matrix &a){
    if((line != a.line) || column != a.column){
        return *this;
    }
    for(int i = 0; i < line; i++){
        for(int j = 0; j < column; j++){
            Matrix[i][j] += a.Matrix[i][j];
        }
    }
    return *this;
}


matrix& matrix::operator -=(const matrix &a){
    *this = *this + (-a);
    return *this;
}


matrix& matrix::operator *=(const matrix &a){
    *this = *this * a;
    return *this;
}


matrix& matrix::operator *=(const double &a){
    *this = *this * a;
    return *this;
}


matrix& matrix::operator /=(const matrix &a){
    if(a.Determinant() == 0){
        return *this;
    }
    *this = *this * a.invert();
    return *this;
}


matrix& matrix::operator /=(const double &a){
    if(a == 0){
        return *this;
    }
    *this = *this * (1 / a);
    return *this;
}












