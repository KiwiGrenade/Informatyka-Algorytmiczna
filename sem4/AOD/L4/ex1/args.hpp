#pragma once
#include <iostream>

struct cmdline_args {
    size_t size = 0;
    bool printFlow = false;

    cmdline_args(int argc, char* argv[]) {
        parseArgs(argc, argv);
    }

    void parseArgs(int argc, char* argv[]) {
        for (int i = 1; i < argc; ++i) {
            std::string_view arg(argv[i]);

            if (arg.starts_with("--")) {
                arg.remove_prefix(2); // Remove the leading "--"

                if (arg == "size") {
                    if (i + 1 < argc) {
                        std::string_view value(argv[i + 1]);
                        try {
                            size = std::stoi(std::string(value));
                        } catch (const std::exception& e) {
                            std::cerr << "Invalid value for --size: " << value << std::endl;
                            exit(1);
                        }
                        ++i; // Skip the value
                    } else {
                        std::cerr << "Missing value for argument: --" << arg << std::endl;
                        exit(1);
                    }
                } else if (arg == "printFlow") {
                    printFlow = true;
                } else {
                    std::cerr << "Unknown argument: --" << arg << std::endl;
                    exit(1);
                }
            }
        }

        if (size == 0) {
            std::cerr << "Missing required argument: --size" << std::endl;
            exit(1);
        }
    }
};
