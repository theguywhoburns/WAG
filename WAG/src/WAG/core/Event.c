#include <WAG/core/Event.h>
#include <WAG/core/Logger.h>

#include <stdlib.h>
#include <string.h>
#include <assert.h>
typedef struct _event_internals {
	EventHandler* event_handlers[EVENT_MAX]; // array that stores vectors of event handlers
} event_internals;

static event_internals* e = NULL;

bool EventSystemInit(void* block, size_t* size){
  if(block == NULL) {
    *size = sizeof(event_internals);
    return true;
  }
	assert(e == NULL && "Attempted to initialize Events twice");
	e = (event_internals*)block;
	memset(e, 0, sizeof(event_internals));
	for (size_t i = 0; i < EVENT_MAX; i++) {
		e->event_handlers[i] = tinyvec_create(EventHandler);
	}
	return true;
}

void EventRegisterHandler(EventType type, EventHandler handler) {
	tinyvec_push(EventHandler, e->event_handlers[type], handler);
}

bool EventDispatch(EventType type, Event* event) {
	for(size_t i = 0; i < tinyvec_length(e->event_handlers[type]); i++) {
		if (!e->event_handlers[type][i](event)) {
			WAGERROR("Event handler failed");
			return false;
		}
	}
	return true;
}

void EventSystemShutdown() {
	for (size_t i = 0; i < EVENT_MAX; i++) {
		tinyvec_destroy(e->event_handlers[i]);
	}
	e = NULL;
}