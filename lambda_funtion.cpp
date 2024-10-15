#include <iostream>
int main() {
	int a[] = {1, 3, 5, 0, 7, 2, 4, 100, 22};
	auto swap_max = [](int &x, int &y)->bool {
		if (x > y) {
			int t = x;
			x = y;
			y = t;
			return true;
		}
		return false;
	};
	for (int n = sizeof(a)/sizeof(int); n > 1; n--)
		for (auto i = 1; i < n; i++)
			swap_max(a[i-1], a[i]);
	auto show = [](int x) { std::cout << x << std::endl; };
	for (auto i = 0; i < sizeof(a)/sizeof(int); i++)
		// std::cout << a[i] << std::endl;
		show(a[i]);
	return 0;
}
