#pragma once
#include "..//..//utils//_Utils.h"
#include "..//..//core//models//headers//Feedback.h"
#include "BaseRepository.h"
#include <fstream>

class FeedbackRepository : public BaseRepository {
private:
	Vector<Feedback*> feedbacks;
	static constexpr String FEEDBACKS_DATA_FILE_NAME = "..//..//data//feedbacks.dat";

	FeedbackRepository() = default;

	const Vector<Feedback*>& getFeedbacks();
	const Feedback* getById(const String& id);

	void add(Feedback* feedback);
	void remove(const Feedback* feedback);

	void load() override;
	void save() const override;
	void free() override;

	friend class System;
};