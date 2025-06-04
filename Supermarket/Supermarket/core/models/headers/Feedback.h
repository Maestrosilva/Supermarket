#pragma once
#include "..//..//..//utils//_Utils.h"

class Feedback : public Serializable{
private:
	const String workerId;
	const String description;
	const String date;

public:
	Feedback() = default;
	Feedback(const String& worker, const String& description);

	const String getWorkerId() const;
	const String& getDescription() const;
	const String& getDate() const;

	String toString() const;

	void serialize(std::ostream& os) const override;
	void deserialize(std::istream& is) override;
};