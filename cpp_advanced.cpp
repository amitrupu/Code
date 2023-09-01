#include <iostream>
#include <functional>
using namespace std;

// lamda
void lambda_test() {
	int a = 10, b = 20;
	auto max = [] (int &a, int &b)->int& {
		return (a>b)? a: b;
	};
	[&](function<int&(int&,int&)> f) {
		cout << f(a,b) << endl;
	}(max);
	[&](function<int&(int&,int&)> f) {
		f(a,b) = 0;
	}(max);
	cout << a << " " << b << endl;
}

int main() {
	lambda_test();
	return 0;
}
