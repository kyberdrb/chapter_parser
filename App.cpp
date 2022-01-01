#include "App.h"

App::App(string inputFilePath) :
    parser
        (std::make_unique<Parser>
             (std::move(inputFilePath))
        )
{}

void App::generateFFMPEG_ChapterMetadata() {
    auto chapterTimestamps = parser->extractDataFromChapterTimestampFile();
    // TODO do this instead
    //  auto sessions = parser->extractDataFromChapterTimestampFile();

    printChapterTimestamps(chapterTimestamps);

    // TODO do this instead
    //  std::cout << sessions << std::endl;
}

void App::printChapterTimestamps(vector<std::unique_ptr<Chapter>>& chapterTimestamps) const {
    for (const auto& chapter : chapterTimestamps) {
        std::cout << *chapter << "\n";
    }
}

void App::printChapterTimestamps(vector<std::unique_ptr<Session>>& sessions) const {
    for (const auto& session : sessions) {
        std::cout << *session << "\n";
    }
}
