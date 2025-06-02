#pragma once
#include "..//..//utils//String.h"
#include "Worker.h"

class Warning {
private:
	const Worker* sender;
	String description;

public:
	Warning() = default;
	Warning(const Worker* sender, const String& description);

	const Worker& getSender() const;
	const String& getDescription() const;
};