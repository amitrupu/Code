#include <iostream>
using namespace std;
char calculator_loop(int balance) {
    char c = 'c';
    while (c == 'c') {
        cout << "Balance: " << balance << endl;
        cin >> c;
        if (c == '+' || c == '-') {
            int n;
            cin >> n;
            if (c == '+')
                c = calculator_loop(balance + n);
            else
                c = calculator_loop(balance - n);
        }
        else
            return c;
    }
    return c;
}
char calculator(int balance) {
    cout << "Balance: " << balance << endl;
    char c;
    cin >> c;
    if (c == '+' || c == '-') {
        int n;
        cin >> n;
        if (c == '+')
            c = calculator(balance + n);
        else
            c = calculator(balance - n);
        if (c == 'c')
            c = calculator(balance);
    }
    return c;    
}
int main() {
    calculator(0);
    return 0;
}