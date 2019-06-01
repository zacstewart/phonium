#ifndef CONTROLLER
#define CONTROLLER

class Controller {
  public:
    /**
     * When this controller takes control
     */
    virtual void begin() = 0;

    /**
     * Called every tick of main loop when in control
     */
    virtual void update() = 0;
};

#endif
