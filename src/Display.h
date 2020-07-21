#ifndef SERVICE_DISPLAY
#define SERVICE_DISPLAY

#include <Adafruit_GFX.h>
#include <Adafruit_SharpMem.h>

class Display {
    public:
        Display(Adafruit_GFX &, Adafruit_SharpMem &);

        /**
         * Writes a blank canvas into the device's memory. Does NOT refresh the
         * display. You will have to call refresh afterwards.
         */
        void clear(void);

        Adafruit_GFX &getCanvas();

        /**
         * Performs a full-screen refresh of the display device.
         */
        void refresh(void);

        /** Attempts to perform a partial refresh of the display device. It
         * will determine when a partial refresh is prudent based on:
         *
         * - number of refreshes since last full refresh
         * - size of rewritten area (maybe)
         */
        void partialRefresh(void);

        /**
         * Transfers data from the GFX canvas into the device's memory
         */
        void writeCanvasMemory(void);

    private:
        Adafruit_GFX &canvas;
        Adafruit_SharpMem &device;
};

#endif
