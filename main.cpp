#include "Chapter.h"
#include "Session.h"

#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <memory>

std::vector<std::string> extractDataFromChapterTimestampFile();
std::string& removeLeadingSpaces(std::string &line);
std::vector<std::string> splitLineBySeparators(std::string &line);
void addAccumulatedTextToSeparatedWords(std::vector<std::string> &tokenizedHTML_Line, const std::ostringstream &accumulatedText);
void resetAccumulatedText(std::ostringstream &htmlLineToken);

void printChapterTimestamps(std::vector<std::string> &chapterTimestamps);

int main() {
// Read raw HTML source code from file
// and parse chapter beginning time and chapter name in an ffmpeg chapter metadata format according to
//  https://ikyle.me/blog/2020/add-mp4-chapters-ffmpeg
// and
//  https://topic.alibabacloud.com/a/ffmpegs-understanding-about-timebase_8_8_10257510.html - search for "II: What is the timebase in FFmpeg"
//
// Merge output of the base metadata
//  ffmpeg -i 01-1-Go_Deep_-_Group_Lesson.mp4 -f ffmetadata 01-1-Go_Deep_-_Group_Lesson-metadata.txt
//
// With the output of this program for the corresponding video
//
//  Example of a chapter file
//
//    [CHAPTER]
//    TIMEBASE=1/1
//    START=39
//    END=262
//    title=Crew Introduction
//
//    [CHAPTER]
//    TIMEBASE=1/1
//    START=262
//    END=1299
//    title=Yoga and Stretches
//
//    [CHAPTER]
//    ...

    std::vector<std::string> chapterTimestamps = extractDataFromChapterTimestampFile();

    printChapterTimestamps(chapterTimestamps);

    return 0;
}

std::vector<std::string> extractDataFromChapterTimestampFile() {
    std::ifstream baseMetadataFile;
    baseMetadataFile.open(
            "/home/laptop/Lehrmaterialien/Wim_Hof_Method/Wim_Hof_Method-Fundamentals-Course/01-10-Chapter_times.txt");

    std::string line;

    std::vector<std::string> chapterTimestamps;

    // TODO move 'sessions' container to a separate class 'Sessions'
    std::vector<std::unique_ptr<Session>> sessions;

    // TODO after the 'Sessions' class, move this loop into a 'Parser' class
    while (std::getline(baseMetadataFile, line)) {

        bool hasTheLineText = !line.empty();
        if (hasTheLineText) {
            line = removeLeadingSpaces(line);

            bool doesLineContainSessionName = line.at(0) != '<';
            if (doesLineContainSessionName) {
                auto& sessionName = line;
                chapterTimestamps.push_back(sessionName);

                auto session = std::make_unique<Session>(sessionName);
                sessions.emplace_back(std::move(session));

                continue;
            }

            bool doesLineBeginWithOpeningHTML_Tag = line.at(0) == '<';
            if (doesLineBeginWithOpeningHTML_Tag) {
                std::vector<std::string> separatedWordsFromLine = splitLineBySeparators(line);

                std::string chapterBeginTime{};
                std::string chapterName{};
                for (auto htmlAttribute = separatedWordsFromLine.begin(); htmlAttribute != separatedWordsFromLine.end(); ++htmlAttribute) {
                    // extractChapterBeginTime
                    bool isChapterBeginningTimeFound = htmlAttribute->find("data-time") != std::string::npos;
                    if (isChapterBeginningTimeFound) {
                        ++htmlAttribute;
                        chapterBeginTime = *htmlAttribute;
                        chapterTimestamps.emplace_back(*htmlAttribute);
                        continue;
                    }

                    // extractChapterName
                    bool isChapterNameFound = htmlAttribute->find("vp-panel-item-label") != std::string::npos;
                    if (isChapterNameFound) {
                        ++htmlAttribute;
                        chapterName = *htmlAttribute;
                        chapterTimestamps.emplace_back(*htmlAttribute);
                        continue;
                    }
                }

                bool areChapterDataValid = !(chapterName.empty() && chapterBeginTime.empty());
                if (areChapterDataValid) {
                    sessions.back()->addChapter(chapterName, chapterBeginTime);
                }
            }
        }
    }

    for (auto& session : sessions) {
        std::cout << *session << "\n";
    }

    return chapterTimestamps;
}

std::string &removeLeadingSpaces(std::string &line) {
    const auto strBegin = line.find_first_not_of(" \t");
    const auto strEnd = line.find_last_not_of(" \t");
    const auto strRange = strEnd - strBegin + 1;
    line = line.substr(strBegin, strRange);
    return line;
}

std::vector<std::string> splitLineBySeparators(std::string &line) {
    std::vector<std::string> separatedWordsFromLine;
    std::ostringstream textBetweenTokens;
    for (const char character : line) {
        bool isCharacterSeparator =
            character == '<' ||
            character == '"' ||
            character == '=' ||
            character == '>' ||
            character == '/' ||
            character == '\t';

        if (isCharacterSeparator)
        {
            bool hasTokenText = !(textBetweenTokens.str().empty());
            if (hasTokenText) {
                addAccumulatedTextToSeparatedWords(separatedWordsFromLine, textBetweenTokens);
                resetAccumulatedText(textBetweenTokens);
            }
            continue;
        }
        textBetweenTokens << character;
    }
    return separatedWordsFromLine;
}

void addAccumulatedTextToSeparatedWords(std::vector<std::string>& tokenizedHTML_Line, const std::ostringstream &accumulatedText) {
    tokenizedHTML_Line.emplace_back(accumulatedText.str());
}

void resetAccumulatedText(std::ostringstream &htmlLineToken) {
    htmlLineToken.str("");
}

void printChapterTimestamps(std::vector<std::string>& chapterTimestamps) {
    for (const auto& attribute : chapterTimestamps) {
        std::cout << attribute << "\n";
    }
}
