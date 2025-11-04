#include "demo.h"
#include "HomeWindow.h"
#include "flowNetwork.hpp"
#include <stdexcept>

int main() {
	try {

	testFunc();
	}
	catch (std::exception e) {
		std::cout << e.what() << "\n";
	}
	catch (...) {
		std::cout << "Unknonwn exception\n";
	}

	return 0;
}