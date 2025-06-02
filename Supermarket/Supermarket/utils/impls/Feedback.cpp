#include "..//headers//Feedback.h"

void Feedback::getFeedback(const String& command, bool successful) {
	if (!successful) {
		std::cout << "Invalid " << command << " command!" << std::endl;
	}

}