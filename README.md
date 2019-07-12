
          ______________-__
          | _____________ |
          | |           | |
         [| |           | |
          | |  Phonium  | |
         [| |           | |
          | |___________| |
          |_______________|
          |               |
          | "   ]   ^   " |
          |               |
          |  1    2    3  |
          |               |
          |  4    5    6  |
          |               |
          |  7    8    9  |
          |               |
          |  *    0    #  |
          |_______________|

# Phonium

A minimalist, homebrew phone.

# Software Design Principals

Each screen is broken out into a view controller object.

Each controller should reset itself before segueing away, not reset on segueing
into it (`begin`).
