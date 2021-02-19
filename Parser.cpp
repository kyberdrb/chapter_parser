#include "Parser.h"
#include "Sessions.h"

std::vector<std::string> Parser::extractDataFromChapterTimestampFile() {
    std::ifstream baseMetadataFile;
    baseMetadataFile.open(this->inputFilePath);

    std::string line;

    std::vector<std::string> chapterTimestamps;

    //std::vector<std::unique_ptr<Session>> sessions;
    // TODO change previous 'sessions' local var from type 'vector' to custom type 'Sessions'
      auto sessions = std::make_unique<Sessions>;

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
                // extractRequiredChapterInfo
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
                    sessions.back()->addChapter(std::move(chapterName), std::move(chapterBeginTime));
                }
            }
        }
    }

    for (auto& session : sessions) {
        std::cout << *session << "\n";
    }

    //TODO return local var of type 'Sessions'
    return chapterTimestamps;
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