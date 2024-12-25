#pragma once

#include <WAG/platform/platform.hpp>
#include <memory>
#include <type_traits>

namespace WAG::Platform {
class WAG_API ILibrary {
public:
  virtual ~ILibrary() = default;
  template <typename T>
    requires std::is_function<T>::value
  T getProcAddress(const char *name) const {
    return reinterpret_cast<T>(getProcAddress_(name));
  }
  static std::unique_ptr<ILibrary> Create(const char *path);
  virtual void *getHandle() const = 0;

private:
  virtual void *getProcAddress_(const char *name) const = 0;
};

}; // namespace WAG::Platform