#include <iostream>

struct S {
	int a;
	int b;
	int c;
	void out() {
		std::cout << a << " " << b << " " << c << std::endl;
	}
};
int main() {
	S s = {};
	int S::* x[3] = {&S::a, &S::b, &S::c};
	s.*x[0] = 1;
	s.*x[1] = 2;
	s.*x[2] = 3;
	s.out();
	return 0;
}
