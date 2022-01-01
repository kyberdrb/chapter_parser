#include "Session.h"

using std::string;

Session::Session(std::string name) :
    name(std::move(name))
{}

void Session::addChapter(std::string chapterName, std::string chapterBeginTime) {
    auto chapter = std::make_unique<Chapter>(
            std::move(chapterName),
            std::move(chapterBeginTime));

    chapters.emplace_back(std::move(chapter));

    if (this->chapters.size() >= 2) {
        updateForelastChapterEndTime();
    }
}

void Session::updateForelastChapterEndTime() {
    uint_fast32_t forelastElementIndex = chapters.size() - 1 - 1;
    Chapter& forelastChapter = *(chapters.at(forelastElementIndex));
    const string& lastChaperBeginTime = chapters.back()->getBeginTime();
    int lastChapterBeginTimeOneSecBehind = std::stoi(lastChaperBeginTime) - 1;
    const string& lastChapterBeginTimeOneSecBehindAsText = std::to_string(lastChapterBeginTimeOneSecBehind);
    forelastChapter.setEndTime(lastChapterBeginTimeOneSecBehindAsText);
}
