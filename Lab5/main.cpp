#include <iostream>
#include <iomanip>


class Diffur{
public:
    int x3, x2, x1;
    double x, y, func, funcH;
    double h;
    double k1, k2, k3, k4;

    Diffur(){
        x3 = x2 = x1 = 0;
        x = y = h = 0;
        func = funcH = 0;
        k1 = k2 = k3 = k4 = 0;
    }

    Diffur(int x3, int x2, int x1){
        this->x3 = x3;
        this->x2 = x2;
        this->x1 = x1;
        y = 1;
        x = 0;
        h = 0.1;
        func = funcH = 0;
        k1 = k2 = k3 = k4 = 0;
    }

    [[nodiscard]] double Calculate2() const{
        return x3 * (x*x*x) + x2 * (x*x) + x1 * y;
    }

    [[nodiscard]] double Calculate() const{
        return x3 * ((x+h/2)*(x+h/2)*(x+h/2)) + x2 * ((x+h/2)*(x+h/2)) + x1 * (y + h/2 * Calculate2());
    }


    void Print(const std::string& fun) const{
        if(fun == "Ei")
            std::cout << std::fixed << std::setprecision(6) << "|   " << x << "   |   " << y << "   |   " << func << "   |   " << funcH << "   |   \n";
        else{
            std::cout << std::fixed << std::setprecision(6) << "|   " << x << "   |   " << k1 << "   |   " << k2 << "   |   " << k3 << "   |   " << k4 << "   |   " << y << "   |   \n";
        }
    }


    void Eiler(){
        double f;
        for(int i = 0; i <= 10; i++){
            double temp = y;
            f = Calculate();
            y = temp + f * h;
            func = f;
            funcH = f * h;
            Print("Ei");
            x += 0.1;
        }
    }


    void Runge_Kutta(){
        for(int i = 0; i <= 10; i++){
            double temp = y;
            double k1l = h * (x3 * (x*x*x) + x2 * (x*x) + x1 * y);
            double k2l = h * (x3 * ((x + h/2)*(x + h/2)*(x + h/2)) + x2 * ((x + h/2)*(x + h/2)) + x1 * (y + k1l/2));
            double k3l = h * (x3 * ((x + h/2)*(x + h/2)*(x + h/2)) + x2 * ((x + h/2)*(x + h/2)) + x1 * (y + k2l/2));
            double k4l = h * (x3 * ((x + h)*(x + h)*(x + h)) + x2 * ((x + h)*(x + h)) + x1 * (y + k3l));
            y = temp + 1./6 * (k1l + 2 * k2l + 2 * k3l + k4l);
            k1 = k1l;
            k2 = k2l;
            k3 = k3l;
            k4 = k4l;

            Print("Ru");
            x += 0.1;
        }
    }
};


int main(int argc, char* argv[]) {

    Diffur dif(-2, 2, 5);
    std::cout << "|   " << "x[i]   " << "    |   " << "y[i]   " << "    |   " << "f[i]   " << "    |   " << "h * f[i]   " << "|\n";
    dif.Eiler();

    std::cout << "\n\n";

    Diffur runge(-2, 2, 5);
    std::cout << "|   " << "x[i]    " << "   |   " << "k1      " << "   |   " << "k2      " << "   |  " << "k3       " << "   |   " << "k4         |" << " y[i]         " << "|\n";
    runge.Runge_Kutta();



    return 0;
}
