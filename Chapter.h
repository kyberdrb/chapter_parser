#pragma once

#include <string>
#include <ostream>

using std::string;

class Chapter {
public:
    Chapter(std::string name, std::string beginTime);
    void setEndTime(std::string time);

    friend std::ostream& operator<<(std::ostream& out, const Chapter& chapter) {
        out << "name: " << chapter.name << " beginTime: " << chapter.beginTime << " endTime: " << chapter.endTime;
        return out;
    }

private:
    string name;
    string beginTime;
    string endTime;
};
