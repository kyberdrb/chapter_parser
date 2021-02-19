#include "App.h"

App::App(string inputFilePath) :
    parser
        (std::make_unique<Parser>
             (std::move(inputFilePath))
        )
{}

void App::generateFFMPEG_ChapterMetadata() {
    std::vector<string> chapterTimestamps = parser->extractDataFromChapterTimestampFile();
    //TODO
    // auto sessions = parser->extractDataFromChapterTimestampFile();

    printChapterTimestamps(chapterTimestamps);

    //TODO
    // std::cout << sessions << std::endl;
}

void App::printChapterTimestamps(vector<string>& chapterTimestamps) {
    for (const auto& attribute : chapterTimestamps) {
        std::cout << attribute << "\n";
    }
}
