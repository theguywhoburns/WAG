#include <WAG/WAG.hpp>
#include <WAG/platform/Window.hpp>
#include <WAG/platform/platform.hpp>
#include <WAG/util.hpp>

using namespace WAG;
using namespace WAG::Util;
int main() {
  Engine instance({"test", 1280, 720});
  return instance.run();
}
