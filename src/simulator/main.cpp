#include "Simulator.h"

#include <tinyformat.h>
#include <cxxopts.h>

int main(int argc, char *argv[]) {

    cxxopts::Options options(argv[0], " - Fluid Simulator");

    pbs::SimulatorSettings settings;

    options.add_options()
    ("h,help", "Print help")
    ("width", tfm::format("Display Width (default: %d)", settings.width), cxxopts::value<int>(settings.width), "N")
    ("height", tfm::format("Display Height (default: %d)", settings.height), cxxopts::value<int>(settings.height), "N")
    ("duration", tfm::format("Duration (default: %.1f s)", settings.duration), cxxopts::value<float>(settings.duration), "s")
    ("timescale", tfm::format("Time Scaling (default: %.1f)", settings.timescale), cxxopts::value<float>(settings.timescale), "")
    ("framerate", tfm::format("Frame Rate (default: %.1f)", settings.framerate), cxxopts::value<float>(settings.framerate), "")
    ("input", "Input files", cxxopts::value<std::vector<std::string>>())
    ;

    options.parse_positional("input");

    // Parse command line arguments
    try {
        options.parse(argc, argv);
    } catch (const std::exception &e) {
        std::cerr << "Error during command line parsing: " << e.what() << std::endl;
        return -1;
    }

    // Show help if requested
    if (options.count("help")) {
        std::cout << options.help() << std::endl;
        return 0;
    }

    if (options.count("input") != 1) {
        std::cerr << "Provide a scene file!" << std::endl << std::endl;
        std::cout << options.help() << std::endl;
        return 0;
    }
    settings.filename = options["input"].as<std::vector<std::string>>().front();

    nanogui::init();
    std::unique_ptr<pbs::Simulator> screen(new pbs::Simulator(settings));
    nanogui::mainloop();
    nanogui::shutdown();

    return 0;
}