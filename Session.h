#pragma once

#include "Chapter.h"

#include <memory>
#include <vector>

class Session {
public:
    explicit Session(std::string name);

    // TODO MythBusting:
    // Do 'const string&' arguments are copied or moved?
    // Is 'const string&' really slower than pass by value 'string' and then do a 'std::move'?
    // Or it's just another myth? I'll maybe try it out with custom objects with explicitely defined copy and move ctors
    // and copy and move operators, and set breakpoints in each of them, to see, whether the copy or the move version
    // had been called.
    void addChapter(std::string sessionName, std::string chapterName, std::string chapterBeginTime);
    //void addChapter(const std::string& chapterName, const std::string& chapterBeginTime);

    friend std::ostream& operator<<(std::ostream& out, const Session& session) {
        // TODO iterate all chapters in the vector and append them in the 'out' stream
        out << session.name << ": " << session.chapters.size() << "\n";
        return out;
    }

private:
    std::string name;
    std::vector<std::unique_ptr<Chapter>> chapters;
};
