#include <WAG/WAG.hpp>
#include <WAG/platform/Window.hpp>
namespace WAG {
Engine::Engine(EngineConfig config) {
  mWindow = Platform::IWindow::Create(config.name, config.width, config.height,
                                      "img.ico");
}

int Engine::run() {
  mWindow->show();
  while (mWindow->isOpen()) {
    Input::InputSystem::get().Update();
    Platform::IWindow::Update();
  }
  return 0;
}

Engine::~Engine() = default;

}; // namespace WAG