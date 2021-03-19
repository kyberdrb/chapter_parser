#pragma once

#include "Chapter.h"
#include "Session.h"
#include "Sessions.h"

//TODO tidy up includes
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <memory>

using std::string;

class Parser {
public:
    explicit Parser(string inputFilePath) :
        inputFilePath(std::move(inputFilePath))
    {}

    std::vector<std::string> extractDataFromChapterTimestampFile();
    // TODO do this instead
    //  Sessions extractDataFromChapterTimestampFile();

private:
    std::string removeLeadingSpaces(std::string& line);
    std::vector<std::string> splitLineBySeparators(std::string& line);
    void addAccumulatedTextToSeparatedWords(std::vector<std::string>& tokenizedHTML_Line, const std::ostringstream& accumulatedText);
    void resetAccumulatedText(std::ostringstream& htmlLineToken);

    string inputFilePath;
};
