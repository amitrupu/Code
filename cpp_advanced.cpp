#include <iostream>
#include <memory>
#include <functional>
using namespace std;

vector<function<void()>> func_pool {
// lamda
[]() {
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
},

// enum class
[]() {
	enum class X {one, two, three} x;
	enum class Y {zero, one, two, three} y;
	x = X::two;
	y = Y::two;
	cout << (x == X::two) << " " << (y > Y::zero) << endl;
},

// array initialization and shared_ptr
[]() {
	shared_ptr<int> p (new int[10] {10}, [](int *p) { delete[] p; });
	shared_ptr<int> q = make_shared<int>(10);
	for (auto i = 0; i < 10; i++) {
		cout << p.get()[i] << " ";
	}
	cout << endl;
	q = p;
}
};

int main() {
	for (auto func : func_pool) {
		func();
	}
	return 0;
}
