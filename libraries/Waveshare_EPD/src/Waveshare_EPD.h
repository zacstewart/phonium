#ifndef WAVESHARE_EPD
#define WAVESHARE_EPD

// Pin definitions. TODO: make these parameters
#define RST_PIN  8
#define DC_PIN   9
#define CS_PIN   10
#define BUSY_PIN 7

// Commands
#define CMD_DRIVER_OUTPUT_CONTROL       0x01
#define CMD_DEEP_SLEEP_MODE             0x10
#define CMD_DATA_ENTRY_MODE             0x11
#define CMD_SW_RESET                    0x12
#define CMD_MASTER_ACTIVATION           0x20
#define CMD_DISPLAY_UPDATE_CTRL_2       0x22
#define CMD_WRITE_BW_RAM                0x24
#define CMD_SET_RAM_X_POSITIONS         0x44
#define CMD_SET_RAM_Y_POSITIONS         0x45
#define CMD_SET_RAM_X_ADDRESS_COUNTER   0x4E
#define CMD_SET_RAM_Y_ADDRESS_COUNTER   0x4F

class Waveshare_EPD  {
    public:
        Waveshare_EPD(void);
        ~Waveshare_EPD(void);
        bool begin(void);
        void clear(void);
        void reset(void);
        void sleep(void);
        void waitUntilIdle(void);

    private:
        void sendCommand(unsigned char);
        void sendData(unsigned char);
        void spiTransfer(unsigned char);
};

#endif
