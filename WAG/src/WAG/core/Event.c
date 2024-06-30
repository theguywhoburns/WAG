#include <WAG/core/Event.h>
#include <WAG/core/Logger.h>

#include <stdlib.h>
#include <string.h>
#include <assert.h>
typedef struct _event_internals {
	EventHandler* event_handlers[EVENT_MAX]; // array that stores vectors of event handlers
} event_internals;

static event_internals* e = NULL;

void EventSystemInit(void* block, size_t* size){
  if(block == NULL) {
    *size = sizeof(event_internals);
    return;
  }
	assert(e == NULL && "Attempted to initialize Events twice");
	e = (event_internals*)block;
	memset(e, 0, sizeof(event_internals));
	for (size_t i = 0; i < EVENT_MAX; i++) {
		e->event_handlers[i] = tinyvec_create(EventHandler);
	}
}

void EventRegisterHandler(EventType type, EventHandler handler) {
	tinyvec_push(EventHandler, e->event_handlers[type], handler);
}

bool EventDispatch(Event* event) {
	for (size_t i = 0; i < EVENT_MAX; i++) {
		for(size_t j = 0; j < tinyvec_length(e->event_handlers[i]); j++) {
			if (!e->event_handlers[i][j](event)) {
				WAGERROR("Event handler failed");
				return false;
			}
		}
	}//let me explore the Engine.c and the rest of the code a bit more
	return true;
}

void EventSystemShutdown() {
	for (size_t i = 0; i < EVENT_MAX; i++) {
		tinyvec_destroy(e->event_handlers[i]);
	}
	e = NULL;
}