#include <WAG/platform.hpp>
#include <WAG/util.hpp>
#include <iostream>

using namespace WAG;
using namespace WAG::Util;
int main() {
  auto dpi = Platform::getScreenDpi();
  auto res = Platform::getScreenResolution();
  std::cout << "DPI: " << dpi << std::endl;
  std::cout << "Resolution: " << std::get<0>(res) << "x" << std::get<1>(res)
            << std::endl;

  auto wnd = Platform::IWindow::Create("WAG", 800, 600);
  wnd->show();
  while (wnd->isOpen()) {
    Platform::IWindow::Update();
  }

  return 0;
}
