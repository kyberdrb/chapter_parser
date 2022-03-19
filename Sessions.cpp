#include "Sessions.h"

void Sessions::add_session(std::unique_ptr<Session> session) {
    this->sessions.emplace_back(std::move(session));
}

void Sessions::add_chapter_to_last_session(string chapterName, string chapterBeginTime) {
    this->sessions.back()->addChapter(
        std::move(chapterName),
        std::move(chapterBeginTime));
}
