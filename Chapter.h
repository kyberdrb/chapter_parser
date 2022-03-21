#pragma once

#include <string>
#include <ostream>

class Chapter {
public:
    Chapter(std::string name, std::string beginTime);

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
        out << "[CHAPTER]" << "\n";
        out << "TIMEBASE=1/1" << "\n";
        out << "START=" << chapter.beginTime << "\n";  // 39

        // fix ffmpeg chapter metadata integration error:
        //     "[ffmetadata @ 0x5620c003ee80] Expected chapter end timestamp, found END=."
        //   but the ffmpeg utility fixes it automatically by itself during metadata integration
        //   by setting the END of the last chapter to the end of the video
//        if (chapter.endTime.empty()) {
//            chapter.endTime = std::to_string(
//                    std::stoi(chapter.beginTime) + 1);
//        }

        out << "END=" << chapter.endTime << "\n";      // 262
        out << "title=" << chapter.name << "\n";       // Crew Introduction
        out << "\n";                                   //[empty line after each CHAPTER entry]

        //out << "name:" << chapter.name << ";\tbeginTime:" << chapter.beginTime << "\tendTime:" << chapter.endTime;
        return out;
    }

private:
    std::string name;

    // TODO change from string to uint_fast32_t - less conversions in program when doing arithmetics
    std::string beginTime;
    //uint_fast32_t beginTime;

    // TODO change from string to uint_fast32_t
    std::string endTime;
};
