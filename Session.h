#pragma once

#include "Chapter.h"

#include <memory>
#include <vector>

class Session {
public:
    explicit Session(std::string name);

    void addChapter(std::string sessionName, std::string chapterName, std::string chapterBeginTime);

    friend std::ostream& operator<<(std::ostream& out, const Session& session) {
        for (const auto& chapter : session.chapters) {
            out << *chapter << "\n";
        }

        return out;
    }

private:
    std::string name;
    std::vector<std::unique_ptr<Chapter>> chapters;

    void updateForelastChapterEndTime();
};
