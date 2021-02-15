#pragma once

#include "Chapter.h"

#include <memory>
#include <vector>

class Session {
public:
    explicit Session(std::string name);

    // Do 'const string&' arguments are copied or moved?
    // Is 'const string&' really slower than pass by value and then do a 'std::move'?
    // Or it's just another myth?
    void addChapter(const std::string& chapterName, const std::string& chapterBeginTime);

    friend std::ostream& operator<<(std::ostream& out, const Session& section) {
        out << section.name << ": " << section.chapters.size() << "\n";
        return out;
    }

private:
    std::string name;
    std::vector<std::unique_ptr<Chapter>> chapters;
};
