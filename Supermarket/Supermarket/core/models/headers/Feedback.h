#pragma once
#include "..//..//..//utils//_Utils.h"

class Feedback : public Serializable{
private:
	String id;
	String workerId;
	String description;
	String date;

public:
	Feedback() = default;
	Feedback(const String& workerId, const String& description);

	const String& getId() const;
	const String& getWorkerId() const;
	const String& getDescription() const;
	const String& getDate() const;

	String toString() const;

	void serialize(std::ostream& os) const override;
	void deserialize(std::istream& is) override;

	~Feedback() = default;
};