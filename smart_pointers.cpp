#include <iostream>
#include <memory>

class Test {
private:
	int x;
public:
	Test(int i): x(i) { std::cout << "constructor" << std::endl; }
	void show() const { std::cout << "show: " << x << std::endl; }
	~Test() { std::cout << "destructor" << std::endl; }
};

int main() {
	if (false) {
		// Test *p = new Test(3);
		std::unique_ptr<Test> p(new Test(3));
		// std::unique_ptr<Test> p = std::make_unique<Test>(3);
		p->show();
	}
	auto wp_stat = [](const std::weak_ptr<Test> &p) {
		std::cout << (p.expired()? "expired": "live") << ": " << p.use_count() << std::endl; 
		if (!p.expired()) p.lock()->show();
	};
	std::weak_ptr<Test> wp, wq;
	{
		// Test *p = nullptr;
		// std::shared_ptr<Test> p(nullptr);
		std::shared_ptr<Test> p = std::make_shared<Test>(3);
		wp = p;
		wp_stat(wp); wp_stat(wq);
		{
			// Test *q = new Test(4);
			// std::shared_ptr<Test> q(new Test(4));
			std::shared_ptr<Test> q = std::make_shared<Test>(4);
			p = q;
			std::cout << q.use_count() << std::endl;
			wp_stat(wp); wp_stat(wq);
			wq = p;
			wp_stat(wp); wp_stat(wq);
		}
		wp = wq;
		p->show();
		wp_stat(wp); wp_stat(wq);
	}
	wp_stat(wp); wp_stat(wq);


	return 0;
}
