#include "Chapter.h"

Chapter::Chapter(std::string name, std::string beginTime) :
    name(std::move(name)), beginTime(std::move(beginTime))
{}

void Chapter::setEndTime(std::string time) {
    this->endTime = std::move(time);
}
