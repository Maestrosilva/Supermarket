#pragma once
#include "..//..//..//utils//_Utils.h"
#include "Worker.h"

class Manager : public Worker {
private:
	static constexpr String specialCode = "SPEZIALEN_E";

public:
	Manager() = default;
	Manager(const String& firstName, const String& lastName, const String& phoneNumber, unsigned char age, const String& password);

	const Role& getRole() const override;

	void serialize(std::ostream& os) const override;
	void deserialize(std::istream& is) override;

	static bool authenticate(const String& specialCode);
};