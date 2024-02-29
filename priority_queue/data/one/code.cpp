#include <iostream>
#include <queue>
#include <ctime>
#include <cstdlib>

#include "priority_queue.hpp"

void TestConstructorAndPush()
{
	std::cout << "Testing constructors, destructor and push..." << std::endl;
	sjtu::priority_queue<int> pq;
	for (int i = 100; i > 0; --i) {
		pq.push(i);
	}
	while (!pq.empty()) {
		std::cout << pq.top() << " ";
		pq.pop();
	}
	std::cout << std::endl;
	for (int i = 1000; i > 100; --i) {
		pq.push(i);
	}
	sjtu::priority_queue<int> pqBack(pq);
	std::cout << pqBack.size() << std::endl;
	sjtu::priority_queue<int> pqBB;
	for (int i = 10; i <= 10000; ++i) {
		pqBB.push(i);
	}
	std::cout << pqBB.size() << std::endl;
	pqBB = pq;
	std::cout << pqBB.size() << std::endl;
}

void TestSize()
{
	std::cout << "Testing size()" << std::endl;
	sjtu::priority_queue<long long> pq;
	for (int i = 1; i <= 1000; ++i) {
		pq.push(rand());
	}
	std::cout << pq.size() << std::endl;
}

void TestException()
{
	sjtu::priority_queue<int> pq;
	try {
		std::cout << pq.top() << std::endl;
	} catch (...) {
		std::cout << "Throw correctly." << std::endl;
	}
}

struct Natural {
    int x;

    Natural(int _x = 0) { x = _x; }

    friend bool operator<(const Natural &lhs, const Natural &rhs) {
        if (lhs.x < 0 || rhs.x < 0)
            throw sjtu::runtime_error();
        return lhs.x < rhs.x;
    }
};

void TestCompareException() {
	std::cout << "Testing compare exception...";

	sjtu::priority_queue<Natural> pq;
    static int dat[2000], ans[2000];
	int pos = 0;
    for (int i = 1; i <= 1000; ++i) {
        dat[i] = i;
		if (rand() % 10 == 0) 
			dat[i] = -i;
		else ans[++pos] = i;
	}

    for (int i = 1000; i > 1; --i) {
        unsigned int x = rand();
        int p = x % (i - 1) + 1;
        std::swap(dat[i], dat[p]);
    }

    while (dat[1] < 0) {
        unsigned int x = rand();
        int p = x % 1000 + 1;
        std::swap(dat[1], dat[p]);
    }


    for (int i = 1; i <= 1000; ++i) {
        try {
            pq.push(Natural(dat[i]));
        } catch (sjtu::runtime_error) {
            if (dat[i] >= 0)
                return std::cout << std::endl, void();
        }
    }

    for (int i = pos; i; --i) {
        Natural t = pq.top();
        if (t.x != ans[i])
                return std::cout << std::endl, void();
        pq.pop();
    }

    std::cout << "ok." << std::endl;

}

int main(int argc, char *const argv[])
{
	TestConstructorAndPush();
	TestSize();
	TestException();
    TestCompareException();
	return 0;
}
