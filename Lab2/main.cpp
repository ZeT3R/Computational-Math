#include <iostream>
#include <string>
#include <utility>


const double eps = 1E-7;


using namespace std;

struct Elem{
    double i;
    Elem* next;

    Elem(){
        next = nullptr;
    }
    explicit Elem(double i){
        this -> i = i;
        next = nullptr;
    }
};


class Stack{

public:
    Elem* head;

    Stack(){
        head = nullptr;
    }


    double first() const{
        if(head != nullptr){
            return head -> i;
        }
        else{
            //cout << "Our struct is empty ";
            return 0;
        }
    }


    bool empty() const{
        return head == nullptr;
    }


    void pop(){
        if(head != nullptr){
            Elem* p = head;
            head = head -> next;
            delete p;
        }
    }


    void push(double i){
        Elem* el = new Elem(i);
        el -> next = head;
        head = el;
    }


    void print() const{
        Elem*temp = head;
        while(temp != nullptr){
            cout << temp -> i << ' ';
            temp = temp -> next;
        }
        cout << endl;
    }
};


double pow(double a, double n){
    double result = 1;
    int i = 0;
    while (i < n){
        result *= a;
        i++;
    }
    return result;
}


int prior(char v){
    switch(v){

        case '(': return 1;


        case '+':
        case '-': return 2;


        case '*':
        case '/': return 3;

        case '^': return 4;

        default:{
            //cout << "ERROR! Input correct data!";
            return 0;
        }
    }
}


bool if_operator(char c){
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
}


bool if_digit(char c){
    return (isdigit(c) != 0 || c == 'x');
}


void OPN(char *a, char *out){
    Stack steck;
    int i = 0, j = 0;
    while (a[i] != '\0'){
        if (if_digit(a[i])){
            out[j] = a[i];
            j++;
        }

        else if (if_operator(a[i])) {
            if (steck.empty() || prior(steck.first()) < prior(a[i])) {
                steck.push(a[i]);
            } else {
                while (prior(steck.first()) >= prior(a[i]) && !steck.empty()) {
                    out[j++] = steck.first();
                    steck.pop();
                }
                steck.push(a[i]);
            }
        }

        else if (a[i] == '('){
            steck.push(a[i]);
        }
        else if (a[i] == ')'){
            if (steck.empty() || steck.first() == '('){
                //cout << "Input error!";
                exit (1);
            }
            else {
                while (steck.first() != '('){
                    out[j] = steck.first();
                    steck.pop();
                    j++;
                }
            }
            steck.pop();
        }

        i++;
    }

    while (!steck.empty()){
        if (steck.first() == '('){
            //cout << "Input error!";
            exit(1);
        }
        else{
            out[j] = steck.first();
            steck.pop();
            j++;
        }
    }

}



std::string* strparse(std::string& str){
    auto* parsestr = new std::string[30];
    int parse = 0;
    std::string save;
    for(int i = 0; i < str.size(); i++){
        if(isdigit(str[i])){
            int j = i;
            save += str[j];
            j++;
            while(isdigit(str[j])) {
                save += str[j];
                j++;
                i++;
            }
            parsestr[parse] = save;
            parse++;
            save.clear();
        }

        else {
            save += str[i];
            parsestr[parse] = save;
            parse++;
            save.clear();
        }


    }


    return parsestr;
}


double CalculateDeriative(std::string* str, double ans){
    double res;
    for(int i = 0; i < 30; i++){
        if(str[i] == "x"){
            str[i] = to_string(ans);
            if(str[i + 1] == "^") {
                double left = stod(str[i]);
                double right = stod(str[i + 2]);
                str[i] = to_string(int(pow(left, right)));
                str[i + 1].clear();
                str[i + 2].clear();
            }
        }
    }



    int j = 0;
    auto* str2 = new std::string[30];
    for(int i = 0; i < 30; i++){
        if(!str[i].empty()) {
            str2[j] = str[i];
            j++;
        }
    }


    for(int i = 0; i < str2->size() + 10; i++){
        if(str2[i + 1] == "*") {
            double left = stod(str2[i]);
            double right = stod(str2[i + 2]);
            str2[i] = to_string(int(left * right));
            str2[i + 1].clear();
            str2[i + 2].clear();
        }
    }

    j = 0;
    auto* str3 = new std::string[str2->size() + 10];
    for(int i = 0; i < str3->size() + 20; i++){
        if(!str2[i].empty()) {
            str3[j] = str2[i];
            j++;
        }
    }

    double one = stod(str3[0]);
    double two = stod(str3[2]);
    double three = stod(str3[4]);

    char symbol1 = str3[1][0];
    char symbol2 = str3[3][0];

    if(symbol1 == '+' && symbol2 == '+'){
        res = one + two + three;
    }
    else if(symbol1 == '+' && symbol2 == '-')
        res = one + two - three;
    else if(symbol1 == '-' && symbol2 == '+')
        res = one - two + three;
    else
        res = one - two - three;

    std::cout << res << " ";

    return res;
}


std::string Deriative(const char* input,char *out){
    Stack steck;
    std::string deriative;
    auto* strtwo = new std::string[10];
    int j = 0;
    char temp[] = {0};
    double head1, head2;
    double head3 = 0;
    bool trigger = false;
    while(out[j] != '\0'){
        if(if_digit(out[j]) && out[j] != 'x') {
            temp[0] = out[j];
            double temp1 = atof(temp);
            steck.push(temp1);
            if(strtwo[0].empty())
                strtwo[0] = out[j];
            else if(strtwo[1].empty() && !strtwo[0].empty())
                strtwo[1] = out[j];
            else if(strtwo[2].empty() && !strtwo[1].empty())
                strtwo[2] = out[j];
        }

        else if(out[j] == 'x') {
            if(strtwo[0].empty())
                strtwo[0] = out[j];
            else if(strtwo[1].empty() && !strtwo[0].empty())
                strtwo[1] = out[j];
            else if(strtwo[2].empty() && !strtwo[1].empty())
                strtwo[2] = out[j];
            else if(strtwo[3].empty() && !strtwo[2].empty())
                strtwo[3] = out[j];
            else if(strtwo[4].empty() && !strtwo[3].empty())
                strtwo[4] = out[j];
        }


        else if(if_operator(out[j])){
            head1 = steck.first();
            steck.pop();
            head2 = steck.first();
            steck.pop();

            std::string save;

            if(!steck.empty()) {
                char third = steck.first();
                steck.pop();
                save = (to_string(third) + to_string(head2));
                head3 = std::stod(save);
            }


            if(strtwo[0][0] != 'x' && strtwo[1][0] != 'x'  && head3 == 0){
                save = (to_string(int(head2)) + to_string(int(head1)));
                head3 = std::stod(save);
            }


            if(out[j] == '^') {
                if (head3 == 0) {
                    if (out[j - 1] == '3' && input[0] != '-')
                        deriative += (to_string(int(head1 * head2)) + "*x^" + to_string(int(head1 - 1)));
                    else if (out[j - 1] == '3' && input[0] == '-')
                        deriative += ("-" + to_string(int(head1 * head2)) + "*x^" + to_string(int(head1 - 1)));

                    else if (out[j - 1] == '2' && out[j + 2] == '+' && !deriative.empty())
                        deriative += ("+" + to_string(int(head1 * head2)) + "*x");
                    else if (out[j - 1] == '2' && out[j + 2] == '-' && !deriative.empty())
                        deriative += ("-" + to_string(int(head1 * head2)) + "*x");

                    else if (out[j - 1] == '2' && input[0] != '-' && deriative.empty()) {
                        deriative += (to_string(int(head1 * head2)) + "*x");
                    }
                    else if (out[j - 1] == '2' && input[0] == '-' && deriative.empty()) {
                        deriative += ("-" + to_string(int(head1 * head2)) + "*x");
                    }
                }


                else {
                    if (out[j - 1] == '3' && input[0] != '-')
                        deriative += (to_string(int(head3 * head1)) + "*x^" + to_string(int(head1 - 1)));
                    else if (out[j - 1] == '3' && input[0] == '-')
                        deriative += ("-" + to_string(int(head3 * head1)) + "*x^" + to_string(int(head1 - 1)));

                    else if (out[j - 1] == '2' && out[j + 2] == '+' && !deriative.empty())
                        deriative += ("+" + to_string(int(head3 * head1)) + "*x");
                    else if (out[j - 1] == '2' && out[j + 2] == '-' && !deriative.empty())
                        deriative += ("-" + to_string(int(head3 * head1)) + "*x");

                    else if (out[j - 1] == '2' && input[0] != '-' && deriative.empty()) {
                        deriative += (to_string(int(head3 * head1)) + "*x");
                        trigger = true;
                    } else if (out[j - 1] == '2' && input[0] == '-' && deriative.empty()) {
                        deriative += ("-" + to_string(int(head3 * head1)) + "*x");
                        trigger = true;
                    }
                }
            }


            if(head3 == 0) {
                if (out[j] == '*') {
                    if (out[j - 1] == 'x') {
                        if (out[j + 1] == '-')
                            deriative += ("-" + to_string(int(head1)));
                        else if (out[j + 1] == '+')
                            deriative += ("+" + to_string(int(head1)));
                    }
                }
            }
            else {
                if (!trigger) {
                    if (out[j] == '*') {
                        if (out[j - 1] == 'x') {
                            if (out[j + 1] == '-') {
                                deriative += ("-" + to_string(int(head3)));
                            }
                            else if (out[j + 1] == '+') {
                                deriative += ("+" + to_string(int(head3)));
                            }
                        }
                    }
                } else {
                    if (out[j] == '*') {
                        if (out[j - 1] == 'x') {
                            if (out[j + 1] == '-')
                                deriative += ("-" + to_string(int(head3)));
                            else if (out[j + 1] == '+')
                                deriative += ("+" + to_string(int(head3)));

                        }
                    }
                }
            }

            save.clear();
        }
        j++;
        head3 = 0;
        trigger = false;

    }
    return deriative;
}

class MyClass{
public:
    double x1, x2, x3, b, a;
    float cap1, cap2, C;
    std::string funcstr;



    MyClass(){
        x1 = x2 = x3 = b = a = 0;
        cap1 = cap2 = C =0.;
    }


    MyClass(int x3, int x2, int x1, float C){
        this->x1 = x1;
        this->x2 = x2;
        this->x3 = x3;
        this->C = C;
        cap1 = cap2 = 0;
        b = a = 0;
    }

    explicit MyClass(std::string f){
        for(int i = 0; i < f.size(); i++)
            funcstr[i] = f[i];
        b = a = 0;
        cap1 = cap2 = 0;
        x3 = 10;
        x2 = 10;
        x1 = -20;
        C = 8;
    }



    MyClass& operator=(const MyClass &copy)= default;


    double CapCalculate(){
        cap1++;
        cap2--;
        b = cap1;
        a = cap2;
        double rescap1 = x3*(b * b * b) + x2 * (b * b) + x1 * (b) + C;
        double rescap2 = x3*(a * a * a) + x2 * (a * a) + x1 * (a) + C;
        return (rescap1 * rescap2);
    }


    double CalculateP3(double ans) const{
        return(x3*(ans*ans*ans) + x2*(ans*ans) + x1*ans + C);
    }

    double CalculateP2(double ans) {
        char output[100];
        char input[100];
        for(int i = 0; i < 20; i++) {
            input[i] = funcstr[i];
        }

        OPN(input, output);
        std::string funcs = Deriative(input, output);
        std::string* str = strparse(funcs);
        return CalculateDeriative(str, ans);

    }


    double PorkMethod(){
        double c = (b + a) / 2;

        if(CalculateP3(c) == 0)
            return c;

        while(std::abs(a - b) > eps){
            c = (b + a) / 2;
            if(CalculateP3(b) * CalculateP3(c) < 0) {
                a = c;
            }
            else if(CalculateP3(c) * CalculateP3(a) < 0) {
                b = c;
            }
        }
        return c;
    }


    double HORDMethod(){
        while (std::abs(a - b) > eps){
            b = a - (a - b) * CalculateP3(a) / (CalculateP3(a) - CalculateP3(b));
            a = b - (b - a) * CalculateP3(b) / (CalculateP3(b) - CalculateP3(a));
        }
        return a;
    }


    double PoslSearch(){
        while(std::abs(a - b) > eps)
            b += eps;

        return b;
    }


    double Newton(){
        while(std::abs(a - b) > eps){
            b = a - (CalculateP3(a) / CalculateP2(b));
            a = b - (CalculateP3(b) / CalculateP2(a));
        }
        return a;
    }
};


int main(){


//    MyClass first(10, 10, -20, 8);
    MyClass second("2*x^3+2*x^2-2*x+8");

//    do {
//
//        std::cout << "OK\n";
//
//
//    }while(first.CapCalculate() > 0);

    do {

        std::cout << "OK\n";


    }while(second.CapCalculate() > 0);

    double answerNewtontest = second.Newton();
    std::cout << answerNewtontest << "\n";

//    double answerPORK = first.PorkMethod();
//    std::cout << answerPORK << "\n";
//
//    double answerHORD = first.HORDMethod();
//    std::cout << answerHORD << "\n";
//
//    double answerPosl = first.PoslSearch();
//    std::cout << answerPosl << "\n";
//
//    double answerNewton = first.Newton();
//    std::cout << answerNewton << "\n";


    return 0;
}