#include "..//headers//Feedback.h"

Feedback::Feedback(const String& workerId, const String& description) : workerId(workerId), description(description),
id(IdGenerator::next(IdType::FEED)), date(Date::getCurrentDate()) {}

const String& Feedback::getWorkerId() const { return workerId; }

const String& Feedback::getDescription() const { return description; }

const String& Feedback::getDate() const { return date; }

const String& Feedback::getId() const { return id; }

String Feedback::toString() const {
	return workerId + " | " + date + " | " + description;
}

void Feedback::serialize(std::ostream& os) const {
	workerId.serialize(os);
	description.serialize(os);
	date.serialize(os);
}

void Feedback::deserialize(std::istream& is) {
	workerId.deserialize(is);
	description.deserialize(is);
	date.deserialize(is);
}