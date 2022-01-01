#include "App.h"

App::App(string inputFilePath) :
    parser
        (std::make_unique<Parser>
             (std::move(inputFilePath))
        )
{}

void App::generateFFMPEG_ChapterMetadata() {
    // TODO do this instead
    //  auto sessions = parser->extractDataFromChapterTimestampFile();
    auto sessions = parser->extractDataFromChapterTimestampFile();

    // TODO do this instead
    //  std::cout << *sessions << std::endl;
    printChapterTimestamps(sessions);
}

void App::printChapterTimestamps(vector<std::unique_ptr<Session>>& sessions) const {
    for (const auto& session : sessions) {
        std::cout << *session << "\n";
    }
}
