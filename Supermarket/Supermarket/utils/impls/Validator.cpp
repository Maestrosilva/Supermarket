#include "..//headers//Validator.h"

bool isDigit(char ch) {
	return ch > '0' && ch < '9';
}

void Validator::validateName(const String& name) {
	if (name.isBlank()) {
		throw std::invalid_argument("Name cannot be blank or empty!");
	}
	if (name.trimmed().contains(" ")) {
		throw std::invalid_argument("Name cannot contain empty spaces!");
	}
}

void Validator::validatePhoneNumber(const String& phone) {
	const unsigned char phoneNumberLen = 10;
	if (phone.getSize() != phoneNumberLen) {
		throw std::invalid_argument("Phone Number must have 10 digits!");
	}
	for (size_t i = 0; i < phoneNumberLen; i++) {
		if (!isDigit(phone.getChar(i))) {
			throw std::invalid_argument("Phone Number must contain digits only!");
		}
	}
}

void Validator::validateAge(unsigned char age) {
	if (age < 18 || age > 65) {
		throw std::invalid_argument("Age must be between 18 and 65!");
	}
}

void Validator::validatePassword(const String& password) {
	if (password.getSize() < 3) {
		throw std::invalid_argument("Password must be at least 3 symbols long!");
	}
}