#include "HomeWindow.hpp"

int main() {
	try {
		runSimuation();
	}
	catch (std::exception e) {
		std::cout << e.what() << "\n";
	}
	catch (...) {
		std::cout << "Unknonwn exception\n";
	}

	return 0;
}