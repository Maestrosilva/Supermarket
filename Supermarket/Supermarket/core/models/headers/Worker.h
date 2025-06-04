#pragma once
#include "..//..//..//utils//_Utils.h"
#include "System.h"

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

	void serialize(std::ostream& os) const override;
	void deserialize(std::istream& is) override;

	virtual const Role& getRole() const = 0;
	const String& toString() const;

	virtual ~Worker() = default;

	friend class System;
};