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

    friend std::ostream& operator<<(std::ostream& out, Sessions& sessions) {
        for (const auto & session : sessions.sessions) {
            out << session->getSessionName() << "\n";
            out << "\n";

            out << *session;

            auto filenameForChaptersOfSession = session->getSessionName();
            sessions.replaceAllSpacesWithUnderscores(filenameForChaptersOfSession); // for easier working with chapter integration script and/or ffmpeg later on

            // append extension to session name, thus forming a full file name
            filenameForChaptersOfSession += ".chapter_timestamps";

            std::ofstream fout(filenameForChaptersOfSession);

            fout << *session << std::endl;

            out << "---" << "\n";
            out << "\n";
        }

        return out;
    }

private:
    vector<std::unique_ptr<Session>> sessions;

    void replaceAllSpacesWithUnderscores(string& filenameForChaptersOfSession) {
        size_t position;
        while ((position = filenameForChaptersOfSession.find(" ")) != std::string::npos) {
            filenameForChaptersOfSession.replace(position, 1, "_");
        }
    }
};