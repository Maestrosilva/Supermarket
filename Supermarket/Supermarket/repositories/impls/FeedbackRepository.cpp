#include "..//headers//FeedbackRepository.h"

Vector<Feedback*> FeedbackRepository::feedbacks;

const Vector<Feedback*>& FeedbackRepository::getFeedbacks() { return feedbacks; }

const Feedback* FeedbackRepository::getById(const String& id) {
    for (size_t i = 0; i < feedbacks.getLength(); i++) {
        if (feedbacks[i]->getId() == id) {
            return feedbacks[i];
        }
    }
    return nullptr;
}

void FeedbackRepository::add(Feedback* feedback) { feedbacks.push(feedback); }
void FeedbackRepository::remove(const Feedback* feedback) { feedbacks.remove(feedback); }

void FeedbackRepository::load() {
    free();
    std::ifstream file(FEEDBACKS_DATA_FILE_NAME, std::ios::binary);
    if (!file) return;
    size_t length = 0;
    file.read(reinterpret_cast<char*>(&length), sizeof(length));
    for (size_t i = 0; i < length; i++) {
        Feedback* feedback = new Feedback();
        feedback->deserialize(file);
        feedbacks.push(feedback);
        if (!file) break;
    }
    file.close();
}

void FeedbackRepository::save() const {
    std::ofstream file(FEEDBACKS_DATA_FILE_NAME, std::ios::binary | std::ios::trunc);
    if (!file) {
        throw std::runtime_error("Failed to open feedbacks file!");
    }
    size_t length = feedbacks.getLength();
    file.write(reinterpret_cast<const char*>(&length), sizeof(length));
    for (size_t i = 0; i < length; i++) {
        feedbacks[i]->serialize(file);
    }
    file.close();
}

void FeedbackRepository::free() {
    for (size_t i = 0; i < feedbacks.getLength(); i++) {
        delete feedbacks[i];
    }
    feedbacks.clear();
}