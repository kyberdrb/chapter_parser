#pragma once

#include "Session.h"

#include <fstream>
#include <vector>

using std::string;
using std::vector;

class Sessions {
public:
    void add_session(std::unique_ptr<Session> session);
    void add_chapter_to_last_session(string chapterName, string chapterBeginTime);

    friend std::ostream& operator<<(std::ostream& out, const Sessions& sessions) {
        for (const auto & session : sessions.sessions) {
            out << session->getSessionName() << "\n";
            out << "\n";

            out << *session;

            // replace all spaces with underscores in this session name
            auto chaptersForSessionFilename = session->getSessionName();
            size_t pos;
            while ((pos = chaptersForSessionFilename.find(" ")) != std::string::npos) {
                chaptersForSessionFilename.replace(pos, 1, "_");
            }

            // append extension to session name, thus forming a full file name
            chaptersForSessionFilename += ".chapter_timestamps";

            std::ofstream fout(chaptersForSessionFilename);

            fout << *session << std::endl;

            out << "---" << "\n";
            out << "\n";
        }

        return out;
    }

private:
    vector<std::unique_ptr<Session>> sessions;
};