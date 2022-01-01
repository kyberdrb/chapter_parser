#include "Chapter.h"

using std::string;

Chapter::Chapter(string name, string beginTime) :
    name(std::move(name)), beginTime(std::move(beginTime))
{}

string Chapter::getBeginTime() const {
    return this->beginTime;
}

void Chapter::setEndTime(string time) {
    this->endTime = std::move(time);
}
