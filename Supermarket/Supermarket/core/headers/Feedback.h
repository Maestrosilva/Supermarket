#pragma once
#include "..//..//utils//headers//String.h"
#include "..//..//utils//headers//Serializable.h"
#include "..//..//utils//headers//Date.h"

class Feedback : public Serializable{
private:
	const String workerId;
	const String description;
	const String date;

public:
	Feedback(const String& worker, const String& description);

	const String getWorkerId() const;
	const String& getDescription() const;
	const String& getDate() const;

	String toString() const;
};