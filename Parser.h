#pragma once

#include "Chapter.h"

#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

using std::string;

class Parser {
public:
    explicit Parser(string inputFilePath) :
        inputFilePath(std::move(inputFilePath))
    {}

    // TODO do this instead
    //  Sessions extractDataFromChapterTimestampFile();
    //std::vector<std::string> extractDataFromChapterTimestampFile();
    std::vector<std::unique_ptr<Chapter>> extractDataFromChapterTimestampFile();

private:
    std::string removeLeadingSpaces(std::string& line);
    std::vector<std::string> splitLineBySeparators(std::string& line);
    void addAccumulatedTextToSeparatedWords(std::vector<std::string>& tokenizedHTML_Line, const std::ostringstream& accumulatedText);
    void resetAccumulatedText(std::ostringstream& htmlLineToken);

    string inputFilePath;
};
