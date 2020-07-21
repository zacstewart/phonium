# TODO

- [x] Write display driver for EPD
- [x] Normalize C++ formatting
- [x] Move Helper into Common
- [x] Create Services container
  - [x] Put Messaging service into Services
  - [x] Construct all Controllers with Services
  - [x] Put all peripheral interfaces into Services
    - [x] Display
    - [x] Keypad (no controllers currently need KP. They receive key events)
    - [x] FONA
- [x] Mark long-lived things (controllers, resources) as static
- [x] Organize and namespace Controllers
- [ ] Replace SHARP display with EPD
  - [x] Separate GFX and display driver in all controllers
  - [x] Write thin Display abstraction around Waveshare_EPD
  - [ ] Swap out SHARP with EPD in Display abstraction
