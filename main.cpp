#include <iostream>
#include <vector>
#include <thread>
#include "list.h"
#include <Windows.h>
#include <map>

//std::cout container with .at && .size
template<typename T>
void show_all(T& list) {

	for (int i = 0; i < list.size(); i++) {
		std::cout << list.at(i) << " ";
	}
	std::cout << std::endl;
}


int main() {
	Destruct::List<int> list({ 1, 2, 3,4 ,5 ,6 ,7 ,8, 9, 10});

	for (auto x : list) {
		std::cout << x << " ";
	}
	std::cout << std::endl;

	list.insert(list.begin() + 3, 999);

	for (auto x : list) {
		std::cout << x << " ";
	}
	std::cout << std::endl;
	
}