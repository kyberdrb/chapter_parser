#include "Chapter.h"

using std::string;

// TODO add sessionName to constructor attrs
Chapter::Chapter(string sessionName, string name, string beginTime) :
    sessionName(sessionName), name(std::move(name)), beginTime(std::move(beginTime))
{}

string Chapter::getSessionName() const {
    return this->sessionName;
}

string Chapter::getBeginTime() const {
    return this->beginTime;
}

void Chapter::setEndTime(string time) {
    this->endTime = std::move(time);
}
