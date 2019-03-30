#include "deque.hpp"
#include "exceptions.hpp"
#include "utility.hpp"
#include "iostream"
#include <deque>
#include <ctime>
#include "cstring"

using namespace sjtu;
constexpr int max_cnt = 1000000;
int main() {
	srand((unsigned int)time(NULL));
	deque<int> deque_data;
	std::deque<int> stl_deque;

	while (1) {
		char ch[100];
		std::cin >> ch;
		if (strcmp(ch, "insert") == 0) {
			int pos, val;
			std::cin >> pos >> val;
			auto p1 = deque_data.insert(deque_data.begin() + pos, val);
			auto p2 = stl_deque.insert(stl_deque.begin() + pos, val);

			for (auto p : deque_data)
				std::cout << p << " ";
			std::cout << std::endl;
			for (auto p : stl_deque)
				std::cout << p << " ";
			std::cout << std::endl;
			std::cout << (p1 == deque_data.end() ? -1 : *p1) << " " << (p2 == stl_deque.end() ? -1 : *p2) << std::endl;
		}
		else if (strcmp(ch, "erase") == 0) {
			int pos;
			std::cin >> pos;
			auto p1 = deque_data.erase(deque_data.begin() + pos);
			auto p2 = stl_deque.erase(stl_deque.begin() + pos);

			for (auto p : deque_data)
				std::cout << p << " ";
			std::cout << std::endl;
			for (auto p : stl_deque)
				std::cout << p << " ";
			std::cout << std::endl;
			std::cout << (p1 == deque_data.end() ? -1 : *p1) << " " << (p2 == stl_deque.end() ? -1 : *p2) << std::endl;
		}
	}

	return 0;
}