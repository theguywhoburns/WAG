#pragma once

/*
How i think it should work:
```c
ExceprionInfo e;
if(SetException(&e)) {
	WAGERROR("Exception: %ex", e);
	return false;    <-------------------
}																			|	
																			|
TheFunctionThatWillThrowException(); -|
```

```c

```
*/