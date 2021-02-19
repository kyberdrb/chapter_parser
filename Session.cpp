#include "Session.h"

Session::Session(std::string name) :
    name(std::move(name))
{}

void Session::addChapter(std::string chapterName, std::string chapterBeginTime) {
    auto chapter = std::make_unique<Chapter>(
        std::move(chapterName),
        std::move(chapterBeginTime));
    chapters.emplace_back(std::move(chapter));
}

//void Session::addChapter(const std::string& chapterName, const std::string& chapterBeginTime) {
//    auto chapter = std::make_unique<Chapter>(chapterName, chapterBeginTime);
//    chapters.emplace_back(std::move(chapter));
//}
