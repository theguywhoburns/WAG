#include <WAG/WAG.hpp>
#include <WAG/platform/Library.hpp>
#include <WAG/platform/platform.hpp>
#include <WAG/util.hpp>
#include <memory>

#if defined(WAG_PLATFORM_WINDOWS)
#include <Windows.h>
namespace WAG::Platform {
class Win64Library : public ILibrary {
public:
  explicit Win64Library(const char *path) : mHModule(LoadLibraryA(path)) {}
  virtual ~Win64Library() override { FreeLibrary(mHModule); }
  virtual void *getProcAddress_(const char *name) const override {
    return (void *)GetProcAddress(mHModule, name);
  }

  virtual void *getHandle() const override { return mHModule; }

private:
  HMODULE mHModule;
};
std::unique_ptr<ILibrary> ILibrary::Create(const char *path) {
  return std::make_unique<Win64Library>(path);
}

} // namespace WAG::Platform

#endif // defined(WAG_PLATFORM_WINDOWS)