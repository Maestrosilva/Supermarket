#pragma once
#include "..//..//..//utils//_Utils.h"
#include "../..//enums//_Enums.h"

class Worker : public Serializable {
protected:
	String id;
	//String username;
	String firstName;
	String lastName;
	String phoneNumber;
	unsigned char age;
	String password;

public:
	Worker() = default;
	Worker(const String& firstName, const String& lastName, const String& phoneNumber, unsigned char age, const String& password);

	const String& getId() const;
	//const String& getUsername() const;
	const String& getFirstName() const;
	const String& getLastName() const;
	const String& getPhoneNumber() const;
	unsigned char getAge() const;

	void setFirstName(const String& firstName);
	void setLastName(const String& lastName);
	void setPhoneNumber(const String& phoneNumber);
	void setAge(unsigned char age);
	void setId(const String& id);

	void serialize(std::ostream& os) const override;
	void deserialize(std::istream& is) override;

	virtual const Role& getRole() const = 0;
	String toString() const;

	virtual ~Worker();

	friend class WorkerRepository;
};