# TODO

- [x] Write display driver for EPD
- [x] Normalize C++ formatting
- [x] Move Helper into Common
- [ ] Create Services container
  - [x] Put Messaging service into Services
  - [x] Construct all Controllers with Services
  - [ ] Put all peripheral interfaces into Services
    - [x] Display
    - [ ] Keypad (no controllers currently need KP. They receive key events)
    - [ ] FONA
- [ ] Mark long-lived things (controllers, resources) as static
- [ ] Replace SHARP display with EPD
  - [ ] Separate GFX and display driver in all controllers
  - [ ] Write thin Display abstraction around Waveshare_EPD
