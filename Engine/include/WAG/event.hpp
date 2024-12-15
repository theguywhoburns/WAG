#pragma once
#include <WAG/WAG.hpp>

#include <algorithm>
#include <functional>
#include <mutex>
#include <utility>
#include <vector>

namespace WAG::Event {

// Forward declaration for ScopedListener
template <typename Event> class WAG_API ScopedListener;

template <typename Event> class WAG_API Bus {
public:
  using HandlerFunc = std::function<void(const Event &)>;
  using Priority = int;

  // Adds a listener with an optional priority
  size_t addListener(HandlerFunc handler, Priority priority = 0) {
    std::lock_guard<std::mutex> lock(mutex_);
    handlers_.emplace_back(++currentId, priority, std::move(handler));
    // Sort handlers based on priority
    std::sort(
        handlers_.begin(), handlers_.end(),
        [](const auto &a, const auto &b) { return a.priority > b.priority; });
    return currentId;
  }

  // Removes a listener by ID
  void removeListener(size_t id) {
    std::lock_guard<std::mutex> lock(mutex_);
    handlers_.erase(std::remove_if(handlers_.begin(), handlers_.end(),
                                   [id](const Handler &handler) {
                                     return handler.id == id;
                                   }),
                    handlers_.end());
  }

  // Dispatches an event to all listeners
  void dispatch(const Event &event) const {
    std::lock_guard<std::mutex> lock(mutex_);
    // Copy handlers to avoid issues during dispatch
    auto handlersCopy = handlers_;
    for (const auto &handler : handlersCopy) {
      handler.func(event);
    }
  }

private:
  struct WAG_API Handler {
    size_t id;
    Priority priority;
    HandlerFunc func;

    Handler(size_t id_, Priority priority_, HandlerFunc func_)
        : id(id_), priority(priority_), func(std::move(func_)) {}
  };

  mutable std::mutex mutex_;
  std::vector<Handler> handlers_;
  size_t currentId = 0;
};

template <typename Event> class WAG_API ScopedListener {
public:
  ScopedListener(Bus<Event> &bus, size_t id) : bus_(bus), id_(id) {}

  // Disable copy
  ScopedListener(const ScopedListener &) = delete;
  ScopedListener &operator=(const ScopedListener &) = delete;

  // Enable move
  ScopedListener(ScopedListener &&other) noexcept
      : bus_(other.bus_), id_(other.id_) {
    other.id_ = 0;
  }

  ScopedListener &operator=(ScopedListener &&other) noexcept {
    if (this != &other) {
      unregister();
      bus_ = other.bus_;
      id_ = other.id_;
      other.id_ = 0;
    }
    return *this;
  }

  ~ScopedListener() { unregister(); }

  void unregister() {
    if (id_ != 0) {
      bus_.removeListener(id_);
      id_ = 0;
    }
  }

private:
  Bus<Event> &bus_;
  size_t id_;
};

class WAG_API Dispatcher{
  public :
      // Adds a listener for a specific event type with an optional priority
      template <typename Event>
      size_t addListener(std::function<void(const Event &)> handler,
                         typename Bus<Event>::Priority priority = 0)
          const {return _addListener(handler, priority);
} // namespace WAG::Event

// Adds a listener using a generic callable (e.g., lambda, functor)
template <typename Event, typename Func>
size_t addListener(Func &&func, typename Bus<Event>::Priority priority = 0) {
  auto handler = std::function<void(const Event &)>(std::forward<Func>(func));
  return _addListener<Event>(std::move(handler), priority);
}

// Adds a member function listener
template <typename Event, typename T>
size_t addListener(T *instance, void (T::*func)(const Event &),
                   typename Bus<Event>::Priority priority = 0) {
  auto handler = [=](const Event &event) { (instance->*func)(event); };
  return _addListener<Event>(std::move(handler), priority);
}

// Removes a listener for a specific event type
template <typename Event> void removeListener(size_t id) {
  auto &bus = getBus<Event>();
  bus.removeListener(id);
}

// Dispatches an event to all listeners subscribed to that event type
template <typename Event> void dispatch(const Event &event) const {
  auto &bus = getBus<Event>();
  bus.dispatch(event);
}

// Creates a scoped listener that automatically unregisters when it goes out of
// scope
template <typename Event> ScopedListener<Event> makeScopedListener(size_t id) {
  return ScopedListener<Event>(Bus<Event>::getInstance(), id);
}

template <typename Event> Bus<Event> &getBus() const {
  static Bus<Event> bus;
  return bus;
}

private:
// HACK: this so public addListener don't call themselves
template <typename Event>
size_t _addListener(std::function<void(const Event &)> handler,
                    typename Bus<Event>::Priority priority = 0) const {
  auto &bus = getBus<Event>();
  return bus.addListener(std::move(handler), priority);
}
}
;

} // namespace WAG::Event
