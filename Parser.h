#pragma once

//#include "Session.h"
#include "Sessions.h"

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
    
    std::unique_ptr<Sessions> extractDataFromChapterTimestampFile();

private:
    std::string removeLeadingSpaces(std::string& line);
    std::vector<std::string> splitLineBySeparators(std::string& line);
    void addAccumulatedTextToSeparatedWords(std::vector<std::string>& tokenizedHTML_Line, const std::ostringstream& accumulatedText);
    void resetAccumulatedText(std::ostringstream& htmlLineToken);

    string inputFilePath;
};
