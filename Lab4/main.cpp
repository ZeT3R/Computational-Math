#include <iostream>
#include <string>
const double eps = 1E-6;


class Integral{
public:
    double x3, x2, x1, C;

    Integral(){
        x3 = x2 = x1 = C = 0;
    }

    Integral(double x3, double x2, double x1, double C){
        this->x3 = x3;
        this->x2 = x2;
        this->x1 = x1;
        this->C = C;
    }


    [[nodiscard]] double CalculateP3(double ans) const{
        return(x3*(ans*ans*ans) + x2*(ans*ans) + x1*ans + C);
    }


    [[nodiscard]] double rectangle_right(double a, double b) const{
        double res = 0;
        double previousresult = 1;
        int n = 1;
        while (std::abs(previousresult - res) > eps) {
            n++;
            double h = (b - a) / n;
            previousresult = res;
            res = 0;
            double tempa = a;
            for (int i = 0; i < n; i++) {
                res += CalculateP3(tempa);
                tempa += h;
            }
            res *= h;
        }
        return res;
    }

    
    [[nodiscard]] double rectangle_left(double a, double b) const{
        double res = 0;
        double previousresult = 1;
        int n = 1;
        double h = (b - a) / n;
        while (std::abs(previousresult - res) > eps) {
            n++;
            double tempa = a;
            previousresult = res;
            res = 0;
            for (int i = 0; i < n; i++) {
                res += CalculateP3(tempa);
                tempa += h;
            }
            res *= h;
            h = (b - a) / n;
        }
        return res;
    }


    [[nodiscard]] double trapeciya(double a, double b) const{
        double res = 0;
        double previousresult = 1;
        int n = 1;
        double h = (b - a) / n;
        while (std::abs(previousresult - res) > eps) {
            n++;
            double tempa = a;
            previousresult = res;
            res = 0;
            for (int i = 0; i < n; i++) {
                res += (CalculateP3(tempa) + CalculateP3(tempa + h)) / 2;
                tempa += h;
            }
            res *= h;
            h = (b - a) / n;
        }
        return res;
    }


    [[nodiscard]] double Simpson(double a, double b) const {
        double res = 0;
        double previousresult = 1;
        int n = 1;
        while (std::abs(previousresult - res) > eps) {
            n *= 2;
            //n++; >15:18:14
            double tempa = a;
            previousresult = res;
            res = 0;
            double h = (b - a) / n;
            for(int i = 0; i < n; i++){
                if(i == 0 || i == n - 1){
                    res += CalculateP3(tempa);
                }
                else if (i % 2 != 0){
                    res += 4 * CalculateP3(tempa);

                }
                else{
                    res += 2 * CalculateP3(tempa);
                }
                tempa += h;
            }
            res *= (h / 3);
        }
        return res;
    }
};


int main(){

    Integral test(-8, 5, 5, 8);

    printf("%.6llf", test.rectangle_left(-2, 2));
    std::cout  << "\n";

    printf("%.6llf", test.rectangle_right(-2, 2));
    std::cout  << "\n";

    printf("%.6llf", test.trapeciya(-2, 2));
    std::cout  << "\n";

    printf("%.6llf", test.Simpson(-2, 2));
    std::cout  << "\n";



    return 0;
}