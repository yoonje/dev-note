#include <iostream>
#include <utility>

void showPair(std::pair<int, double> input);
int main(void)
{
	
	std::pair <int, double> p1(1, 1.3);
	std::cout << "p1 " << std::endl;
	showPair(p1);
	std::pair <int, double> p2;
	
	p2 = std::make_pair(2, 2.6);
	std::cout << "p2 " << std::endl;
	showPair(p2);
	
	std::pair <int, double> p3(p1);
	std::cout << "p3: p1 복사 " << std::endl;
	showPair(p3);
	p3.first = 3;
	p3.second = 3.9;
	std::cout << "p3: " << std::endl;
	showPair(p3);
}

void showPair(std::pair<int, double> input)
{
	std::cout << "pair 첫번째 인자 " << input.first << std::endl;
	std::cout << "pair 첫번째 인자 " << input.second << std::endl << std::endl;
}