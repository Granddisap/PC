#include <iostream>
#include <math.h>
#include <vector>
#include <chrono>
#include <omp.h> 
#include <random>


void print_dt(std::chrono::system_clock::time_point t0) {
	auto t1 = std::chrono::system_clock::now();
	std::cout << "dt = " << std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0).count() << "ms" << std::endl;
}

void inputArray(std::vector<int>& arr)
{
	for (unsigned i = 0; i < arr.size(); i++)
	{
		std::cout << "a[" << i << "] = ";
		std::cin >> arr[i];
	}
}

void randomArray(std::vector<int>& arr)
{
	srand(time(NULL));

	const int min = 1;
	const int max = 10;

	for (auto& i : arr)
		i = min + rand() % (max - min + 1);
}

void printArray(std::vector<int>& arr)
{
	for (unsigned i = 0; i < arr.size(); i++)
		std::cout << "a[" << i << "] = " << arr[i] << std::endl;
}

double processParallel(std::vector<int>& arr)
{
	double sum = 1;
	#pragma omp parallel for reduction(*:sum)
	for (int i = 0; i < arr.size(); i++) {
		sum *= arr[i] + 1;
	}
	return sum;
	//как распределяется работа
}

double process(std::vector<int>& arr)
{
	double sum = 1;
	for (unsigned i = 0; i < arr.size(); i++) {
		sum *= arr[i] + 1;
	}
	return sum;
}

int main()
{
	omp_set_num_threads(6);
	std::vector<int> arr;
	int array_size = 0;
	std::cout << "max threads: " << omp_get_max_threads() << std::endl;

	do 
	{
		std::cout << "Input n: ";
		std::cin >> array_size;
		if (array_size == -21) array_size = 500000000;
	} while (array_size < 1);

	arr.resize(array_size);

	unsigned c = 0;
	do 
	{	
		std::cout << "Input 1 for input array\n";
		std::cout << "Input 2 for generate random array\n";
		std::cout << "Input number: ";
		std::cin >> c;

		if ((c != 1) & (c != 2)) 
			std::cout << "Wrong number!!! Repeat please\n\n";
	} while ((c != 1) & (c != 2));
	
	if (c == 1)
		inputArray(arr);
	else
		randomArray(arr);
	
	std::cout << std::endl;


	auto t0 = std::chrono::system_clock::now();
	auto res1 = sqrt(abs(process(arr)));
	std::cout << "NoParallel ";
	print_dt(t0);
	t0 = std::chrono::system_clock::now();
	auto res2 = sqrt(abs(processParallel(arr)));
	std::cout << "Parallel ";
	print_dt(t0);

	std::cout << "res1: " << res1 << std::endl;
	std::cout << "res2: " << res2 << std::endl;

	return 0;
}
