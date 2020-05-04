#include "file_utils.h"
#include <string>
#include <filesystem>

using namespace std;

filesystem::path FileUtils::get_game_dir() {
#ifdef _WIN32
  return getenv("APPDATA") + "/iso-tanks/";
#elif _WIN64
  return getenv("APPDATA") + "/iso-tanks/";
#elif __APPLE__ || __MACH__
  return get_home_dir() / "Library/Application Support/iso-tanks/";
#elif __linux__
  return get_home_dir() / ".local/share/iso-tanks/";
#else
  throw "Unknown operating system!";
#endif
}

filesystem::path FileUtils::get_home_dir() {
#ifdef _WIN32
  return getenv("HOMEPATH");
#elif _WIN64
  return getenv("HOMEPATH");
#elif __APPLE__ || __MACH__
  return getenv("HOME");
#elif __linux__
  return getenv("HOME");
#else
  throw "Unknown operating system!";
#endif
}
