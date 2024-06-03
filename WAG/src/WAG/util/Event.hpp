#pragma once
#include <unordered_map>
#include <vector>
#include <typeindex>

class Event;
using EventCallback = void (*)(Event*);
using _FastEventCallback = void (*)(_FastEvent);

class _FastEvent {
public:
	enum FastEvents {
		WindowResize,
		WindowMove,
		WindowClose,
		WindowHide,

		KeyPressed,
		KeyReleased,
		MouseBtnPressed,
		MouseBtnReleased,
		MouseMoved,
		MouseMovedRaw,

		Error,
		Shutdown
	};

	union msg {
		uint64_t ul[8];
		uint32_t ui[16];
		uint16_t us[32];
		uint8_t  uc[64];
	};
	
	static std::vector<std::vector<_FastEventCallback>> callback_array;
	FastEvents type;
	void Fire() {
		for (auto callback : callback_array[type])
			callback(this);
	}
};

class Event {
public:
	Event() = default;
	virtual ~Event() = default;
	static std::unordered_map<std::type_index, std::vector<EventCallback>> events;
	template<class T>
	static void Register(EventCallback c) {
		static_assert(std::is_base_of<Event, T>::value, "this class should be derived from Event");
		if (events.find(typeid(T)) != events.end())
			events[typeid(T)].push_back(c);
		else
			events[typeid(T)] = { c };
	}
	void Fire() {
		for (auto callback : events[typeid(*this)])
			callback(this);
	}
};
