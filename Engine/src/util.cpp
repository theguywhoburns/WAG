#include <WAG/util.hpp>

namespace WAG::Util {
namespace Console {
std::string getColorStr(const RGB &rgb, ConsoleLayer layer) {
  if (layer == ConsoleLayer::Both) {
    return "\x1B[38;2;" + std::to_string(rgb.r.value()) + ';' +
           std::to_string(rgb.g.value()) + ';' + std::to_string(rgb.b.value()) +
           'm' + "\x1B[48;2;" + std::to_string(rgb.r.value()) + ';' +
           std::to_string(rgb.g.value()) + ';' + std::to_string(rgb.b.value()) +
           'm';
  }
  return "\x1B[" + std::to_string(static_cast<int>(layer)) + ";2;" +
         std::to_string(rgb.r.value()) + ';' + std::to_string(rgb.g.value()) +
         ';' + std::to_string(rgb.b.value()) + 'm';
}

void resetColor() { std::cout << "\x1B[0m" << std::flush; }

std::string resetColorStr() { return "\x1B[0m"; }

void clearScreen() { std::cout << "\x1B[2J"; }
}; // namespace Console
}; // namespace WAG::Util
