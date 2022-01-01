#include "Chapter.h"

using std::string;

Chapter::Chapter(string sessionName, string name, string beginTime) :
    sessionName(sessionName), name(std::move(name)), beginTime(std::move(beginTime))
{}

Chapter::Chapter(string sessionName, string name, string beginTime, string endTime) :
        sessionName(sessionName),
        name(std::move(name)),
        beginTime(std::move(beginTime)),
        endTime(std::move(endTime))
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
