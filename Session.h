#pragma once

#include "Chapter.h"

#include <memory>
#include <vector>

class Session {
public:
    explicit Session(std::string name);

    void addChapter(std::string chapterName, std::string chapterBeginTime);
    std::string getSessionName() const;

    friend std::ostream& operator<<(std::ostream& out, const Session& session) {
        //out << session.name << "\n";
        out << "\n";

        for (const auto& chapter : session.chapters) {
            out << *chapter;
        }

        return out;
    }

private:
    std::string name;
    std::vector<std::unique_ptr<Chapter>> chapters;

    void updateForelastChapterEndTime();
};
