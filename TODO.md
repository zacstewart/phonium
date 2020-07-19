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
- [ ] Replace SHARP display with EPD
  - [ ] Separate GFX and display driver in all controllers
  - [ ] Write thin Display abstraction around Waveshare_EPD