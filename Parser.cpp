#include "Parser.h"

std::unique_ptr<Sessions> Parser::extractDataFromChapterTimestampFile() {

    std::ifstream baseMetadataFile;
    baseMetadataFile.open(this->inputFilePath);

    std::string line;
    std::string sessionName;
    auto sessions = std::make_unique<Sessions>();

    while (std::getline(baseMetadataFile, line)) {

        bool hasTheLineText = !line.empty();
        if (hasTheLineText) {
            line = removeLeadingSpaces(line);

            bool doesLineContainSessionName = line.at(0) != '<';
            if (doesLineContainSessionName) {
                sessionName = line;

                auto session = std::make_unique<Session>(sessionName);
                sessions->add_session(std::move(session));

                // addStartingChapter
                sessions->add_chapter_to_last_session("Start", "0");

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
                    sessions->add_chapter_to_last_session(
                        std::move(chapterName),
                        std::move(chapterBeginTime));
                }
            }
        }
    }

    return sessions;
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