#pragma once

/*
How i think it should work:
```c
ExceprionInfo e = {0};
if(SetExceptionCatch(&e)) {
  // %ex is a custom formatting symbol... yeah
  WAGERROR("Exception: %ex", e); // Mb place a goto here, idk
  return false;    <-------------------
}                                     |    
                                      |
TheFunctionThatWillThrowException(); -|
```

```c
TheFunctionThatWillThrowException() {
  ThrowException(&e); // <- this is a macro
}
```
*/

#define SetExceptionCatch(e) 
#define ThrowException(e)