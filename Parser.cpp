#include "Parser.h"
//#include "Session.h"

//std::vector<std::string> Parser::extractDataFromChapterTimestampFile() {
std::vector<std::unique_ptr<Chapter>> Parser::extractDataFromChapterTimestampFile() {
    std::ifstream baseMetadataFile;
    baseMetadataFile.open(this->inputFilePath);

    std::string line;
    std::string sessionName;

    //TODO rework to 'std::vector<Session> chapterTimestamps;' for SRP and encapsulation
    std::vector<std::unique_ptr<Chapter>> chapters;

    //std::vector<std::unique_ptr<Session>> sessions;
    // TODO change previous 'sessions' local var from type 'vector' to custom type 'Sessions'
    //  auto sessions = std::make_unique<Sessions>;
    //auto sessions = std::make_unique<Sessions>;

    while (std::getline(baseMetadataFile, line)) {

        bool hasTheLineText = !line.empty();
        if (hasTheLineText) {
            line = removeLeadingSpaces(line);

            bool doesLineContainSessionName = line.at(0) != '<';
            if (doesLineContainSessionName) {
                sessionName = line;

                //auto session = std::make_unique<Session>(sessionName);
                //sessions.emplace_back(std::move(session));

                continue;
            }

            bool doesLineBeginWithOpeningHTML_Tag = line.at(0) == '<';
            if (doesLineBeginWithOpeningHTML_Tag) {
                std::vector<std::string> separatedWordsFromLine = splitLineBySeparators(line);

                std::string chapterBeginTime{};
                std::string chapterName{};
                // extractRequiredChapterInfo
                for (auto htmlAttribute = separatedWordsFromLine.begin(); htmlAttribute != separatedWordsFromLine.end(); ++htmlAttribute) {
                    // extractChapterBeginTime
                    bool isChapterBeginningTimeFound = htmlAttribute->find("data-time") != std::string::npos;
                    if (isChapterBeginningTimeFound) {
                        ++htmlAttribute;
                        chapterBeginTime = *htmlAttribute;
                        continue;
                    }

                    // extractChapterName
                    bool isChapterNameFound = htmlAttribute->find("vp-panel-item-label") != std::string::npos;
                    if (isChapterNameFound) {
                        ++htmlAttribute;
                        chapterName = *htmlAttribute;
                        continue;
                    }
                }

                bool areChapterDataValid = !(chapterName.empty() && chapterBeginTime.empty());
                if (areChapterDataValid) {
                    //sessions.back()->addChapter(std::move(chapterName), std::move(chapterBeginTime));
                    auto chapter = std::make_unique<Chapter>(
                            sessionName,
                            std::move(chapterName),
                            std::move(chapterBeginTime));
                    chapters.emplace_back(std::move(chapter));
                }
            }
        }
    }

//    for (auto& session : sessions) {
//        std::cout << *session << "\n";
//    }

    // TODO deduce end times for each chapter if possible
    //  - the last chapter will not have an end time
    //  - the end time of one chapter is the beginning of the start time of the successing chapter

    //TODO later return local var of type 'Sessions'
    return chapters;
}

std::string Parser::removeLeadingSpaces(std::string& line) {
    const auto strBegin = line.find_first_not_of(" \t");
    const auto strEnd = line.find_last_not_of(" \t");
    const auto strRange = strEnd - strBegin + 1;
    line = line.substr(strBegin, strRange);
    return line;
}

std::vector<std::string> Parser::splitLineBySeparators(std::string& line) {
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

void Parser::addAccumulatedTextToSeparatedWords(std::vector<std::string>& tokenizedHTML_Line, const std::ostringstream& accumulatedText) {
    tokenizedHTML_Line.emplace_back(accumulatedText.str());
}

void Parser::resetAccumulatedText(std::ostringstream& htmlLineToken) {
    htmlLineToken.str("");
}