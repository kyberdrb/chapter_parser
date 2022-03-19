#include "App.h"

App::App(string inputFilePath) :
    parser
        (std::make_unique<Parser>
             (std::move(inputFilePath))
        )
{}

void App::generateFFMPEG_ChapterMetadata() {
    auto sessions = parser->extractDataFromChapterTimestampFile();
    std::cout << *sessions << std::endl;
}
