#include <math.h>
#include <iostream>

#include <thread>
#include <future>

// для предачи функции как параметра
//#include <functional>

#include <chrono>
#include <random>
#include <vector>


void print_dt(std::chrono::system_clock::time_point t0) {
	auto t1 = std::chrono::system_clock::now();
	std::cout << "dt = " << std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0).count() << "ms" << std::endl;
}

void inputArray(std::vector<int>& arr)
{
	for (unsigned i = 0; i < arr.size(); i++)
	{
		std::cout << "arr[" << i << "] = ";
		std::cin >> arr[i];
	}
}

void randomArray(std::vector<int>& arr)
{
	srand(time(NULL));

	const int min = -10;
	const int max = 10;

	for (auto& i: arr)
		i = min + rand() % (max - min + 1);
}

void printArray(std::vector<int>& arr)
{
	for (unsigned i = 0; i < arr.size(); i++)
		std::cout << "a[" << i << "] = " << arr[i] << std::endl;
}

long mulA(std::vector<int>& a)
{
	long mul = 1;
	for (const auto& i : a)
		mul *= i;
	return mul;
}

long sumB(std::vector<int>& b)
{
	long sum = 0;
	for (const auto& i : b)
		sum += i;
	return sum;
}

double processParallel(std::vector<int>& a, std::vector<int>& b)
{
	std::future<long> mul;
	std::future<long> sum;

	mul = std::async(mulA, std::ref(a));
	sum = std::async(sumB, std::ref(b));

	mul.wait();
	sum.wait();

	return double(mul.get() / sum.get());
}

double process(std::vector<int>& a, std::vector<int>& b)
{
	long mul;
	long sum;

	mul = mulA(a);
	sum = sumB(b);


	return double(mul / sum);
}

int main()
{
	std::vector<int> a;
	std::vector<int> b;

	unsigned n;
	unsigned m;

	std::cout << "(a1 * a2 *...* an) / (b1 + b2 +...+ bn)" << std::endl;

	do
	{
		std::cout << "Input n (n>0): ";
		std::cin >> n;
		if (n == -21) n = 500000000;
		else if (n <= 0) std::cout << "Please, repeat";
	} while (n <= 0);

	do
	{
		std::cout << "Input m (m>0): ";
		std::cin >> m;
		if (m == -21) n = 500000000;
		else if (m <= 0) std::cout << "Please, repeat";
	} while (m <= 0);

	a.resize(n);
	b.resize(m);

	unsigned c = 0;
	do
	{
		std::cout << "Input 1 for input arrays\n";
		std::cout << "Input 2 for generate random arrays\n";
		std::cout << "Input number: ";
		std::cin >> c;

		if ((c != 1) & (c != 2))
			std::cout << "Wrong number!!! Repeat please\n\n";
	} while ((c != 1) & (c != 2));

	if (c == 1)
	{
		std::cout << "Input \"a\" array" << std::endl;
		inputArray(a);
		std::cout << std::endl;
		std::cout << "Input \"b\" array" << std::endl;
		inputArray(b);
	}
	else
	{
		randomArray(a);
		randomArray(b);
	}

	auto t0 = std::chrono::system_clock::now();
	double resParallel = processParallel(a, b);
	print_dt(t0);

	t0 = std::chrono::system_clock::now();
	double res = process(a, b);
	print_dt(t0);

	std::cout << "Parallel result: " << resParallel << std::endl;
	std::cout << "Non-Parallel result: " << res << std::endl;

	//printArray(a);
	//printArray(b);
	return 0;
}