#pragma once
#include "..//..//..//utils//_Utils.h"
#include "Worker.h"

class Warning : public Serializable{
private:
	String senderId;
	String description;
	DegreeOfCriticality degree;

public:
	Warning() = default;
	Warning(const Worker* sender, const String& description, const DegreeOfCriticality& degree);

	const String& getSenderId() const;
	const String& getDescription() const;
	const DegreeOfCriticality& getDegreeOfCriticality() const;
	void serialize(std::ostream& os) const override;
	void deserialize(std::istream& is) override;

	~Warning() = default;
};