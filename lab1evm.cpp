#include <iostream>
#include <math.h>
#include <iomanip>

using namespace std;

double Calculate_Pi(int n){
    double pi=0;
    for(int i=0; i<n; i++){
        pi+=((pow(-1, i))/(2*i+1));
    }    
    return 4*pi;
}

int main(void) {
    int N;
    cin >> N;
    if (cin.fail()){
        cout<<"ошибка ввода";
        return 1;
    }
    cout << fixed << setprecision(9) << Calculate_Pi(N);
    return 0;
}

