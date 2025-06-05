#pragma once
#include "..//..//utils//_Utils.h"
#include "..//..//core//models//headers//Feedback.h"
#include "BaseRepository.h"
#include <fstream>

class FeedbackRepository : public BaseRepository {
private:
	Vector<Feedback*> feedbacks;
	static const String FEEDBACKS_DATA_FILE_NAME;

	FeedbackRepository() = default;

	const Vector<Feedback*>& getFeedbacks();
	const Feedback* getById(const String& id);

	void add(Feedback* feedback);
	void remove(Feedback* const feedback);

	void load() override;
	void save() const override;
	void free() override;

	friend class System;
};