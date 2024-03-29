#pragma once

#include "Parser.h"

#include <memory>
#include <string>
#include <vector>

using std::string;
using std::vector;

class App {
public:
    explicit App(string inputFilePath);

    void generateFFMPEG_ChapterMetadata();

private:
    std::unique_ptr<Parser> parser;
};
