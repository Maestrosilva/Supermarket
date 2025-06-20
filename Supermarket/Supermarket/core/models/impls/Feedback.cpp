#include "..//headers//Feedback.h"

Feedback::Feedback(const String& workerId, const String& description) : workerId(workerId), description(description),
id(String::intToString(IdGenerator::next(IdType::FEED))), date(Date::getCurrentDate()) {}

const String& Feedback::getWorkerId() const { return workerId; }

const String& Feedback::getDescription() const { return description; }

const String& Feedback::getDate() const { return date; }

const String& Feedback::getId() const { return id; }

String Feedback::toString() const {
	return String("Id: ") + id + String(" | Cashier Id: ") + workerId + String(" | ") + date + String(" | ") + description;
}

void Feedback::serialize(std::ostream& os) const {
    id.serialize(os);
	workerId.serialize(os);
	description.serialize(os);
	date.serialize(os);
}

void Feedback::deserialize(std::istream& is) {
    id.deserialize(is);
    workerId.deserialize(is);
    description.deserialize(is);
    date.deserialize(is);
}