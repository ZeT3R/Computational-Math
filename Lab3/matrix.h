#pragma once

#include <iostream>

class matrix{

    protected:
        int line;
        int column;
        double **Matrix;

    public:
        matrix(int k, int l);

        matrix(double MMatrix, int k, int l);

        matrix(const double *MMatrix, int k, int l);

        matrix(double **MMatrix, int k, int l);

        matrix(const matrix& other);

        ~matrix();

         static bool my_pow(double degree);

         matrix find_minor(int fbegin, int fend, int sbegin, int send) const;

         double Determinant() const;

         matrix Transpose() const;

         matrix invert()const;

        double& operator()(int ind1, int ind2);

        double* operator[](int ind);

        double at(int ind1, int ind2);

        friend std::ostream& operator<<(std::ostream& out, const matrix& MMatrix);

        friend matrix operator*(const double &a, const matrix &b);

        friend matrix operator*(const matrix &a, const double &b);

        friend matrix operator*(const matrix &a, const matrix &b);

        friend matrix operator +(const matrix &a, const matrix &b);

        friend matrix operator -(const matrix &a);

        friend matrix operator -(const matrix &a, const matrix &b);

        friend matrix operator +(const matrix &a);

        friend matrix operator /(const matrix &a, const matrix &b);

        friend matrix operator /(const matrix &a, const double &b);

        friend matrix operator /(const double &a, const matrix &b);


        matrix& operator =(const matrix &a);

        matrix& operator +=(const matrix &a);

        matrix& operator -=(const matrix &a);

        matrix& operator /=(const double &a);

        matrix& operator /=(const matrix &a);

        matrix& operator *=(const double &a);

        matrix& operator *=(const matrix &a);
};
