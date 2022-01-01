#pragma once

#include <string>
#include <ostream>

class Chapter {
public:
    Chapter(std::string sessionName, std::string name, std::string beginTime);

    std::string getSessionName() const;
    std::string getBeginTime() const;
    void setEndTime(std::string time);

    // Sample output:
    //
    //   [CHAPTER]
    //   TIMEBASE=1/1
    //   START=39
    //   END=262
    //   title=Crew Introduction
    //   [empty line after each CHAPTER entry]
    friend std::ostream& operator<<(std::ostream& out, const Chapter& chapter) {
        //out << "[CHAPTER]" << "\n";
        //out << "TIMEBASE=1/1" << "\n"
        //out << "START=" << this->beginTime << "\n";                           // 39
        //out << "END=" << this->endTime << "\n";                               // 262
        //out << "title=" << this->sessionName << ": " << this->name << "\n";   // Crew Introduction
        //out << "\n";   [empty line after each CHAPTER entry]

        out << "sessionName: " << chapter.sessionName << ";\tname: " << chapter.name << ";\tbeginTime:" << chapter.beginTime << "\tendTime:" << chapter.endTime;
        return out;
    }

private:
    std::string sessionName;
    std::string name;
    std::string beginTime;
    std::string endTime;
};
