#include "App.h"

int main() {
    // TODO load path from argv
    auto app = std::make_unique<App>
            ("/home/laptop/Lehrmaterialien/Wim_Hof_Method/Wim_Hof_Method-Fundamentals-Course/01-10-Chapter_times.txt");
    app->generateFFMPEG_ChapterMetadata();

    return 0;
}