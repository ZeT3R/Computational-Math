#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
using namespace std;


double check(string el){
	double save1, save2, save3;
	string save_, savesecond;
	    for(int i = 0; i < el.length(); i++){
		    if(el[i] == '(') {
                save1 = i + 1;
                if(el[0] == '-'){
                    save3 = 1;
                    while(el[save3] != '/'){
                        savesecond += el[save3];
                        save3++;
                    }
                }
                else{
                    save3 = 0;
                    while(el[save3] != '/'){
                        savesecond += el[save3];
                        save3++;
                    }
                }
		        while(el[save1] != ')'){
                    save_ += el[save1];
                    save1++;
		        }
            }
	    }
    if(save_.empty()){
        return stod(el);
    }
    save1 = stod(save_);
    save2 = stod(savesecond);
	double finres = save2 / sqrt(save1);
	if(el[0] == '-'){
	    return -finres;
	}
	return finres;
}


  double arcsin(double x){
      int n = 0; 
      double a = x; 
      double arcsin = x;
      double eps = 1E-6; 
      while (abs(a) > eps){ 
          a *= (x * x * (2 * n + 1) * (2 * n + 1) / (2 * (n + 1) * (2 * n + 3)));
          arcsin += a; 
          n++; 
      }
      return arcsin;
  }


int main(){
    ifstream fileinput("input.txt");
    string x;
    double c[10];
    for(int i = 0; i < 10; i++){
        fileinput >> x;
        c[i] = check(x);
        
    }

    fileinput.close();

    ofstream fileoutput("output.txt");
    for (int i = 0; i < 10; i++) {
        fileoutput << arcsin(c[i]) << " = Znachenie arcsin(x) dlya znacheniya " << c[i] << endl;
        fileoutput << endl;
    }

    fileoutput.close();

    return 0;
}
