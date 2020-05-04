#ifndef _FILE_UTILS_H
#define _FILE_UTILS_H

#include <filesystem>

class FileUtils {
  public:
    static std::filesystem::path get_game_dir();
    static std::filesystem::path get_home_dir();
    static int get_length(std::filesystem::path filename);
};

#endif
