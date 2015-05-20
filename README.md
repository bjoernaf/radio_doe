# radio_doe

1. Install arduino-mk: apt-get install arduino-mk
2. Give user access to Arduino device: usermod -a -G dialout *username*
2. Connect Arduino via USB
3. In either directory: make clean; make; make upload (must clean every time?)
4. Add any other steps to this readme.

**General note**: To compile .c or .cpp files (as opposed to .ino etc) files for 
the Arduino, you must create your own main function, as this is not done by the
compiler. Basically, you can create a main.cpp file like this:

```
#include <Arduino.h>

/**
 * Initial setup
 */
void setup() {

}

/**
 * Control loop
 */
void loop() {

}

/**
 * Program entry point.
 */
int main() {
    init(); // In Arduino.h
    setup();
    for(;;) {
	loop();
    }
}
```
