#ifndef WAVESHARE_EPD
#define WAVESHARE_EPD

/*******************************************************************************
 *
 * Color pallet
 *
 ******************************************************************************/
#define EPD_BLACK 0
#define EPD_WHITE 1

/*******************************************************************************
 *
 * Pin definitions. TODO: make these parameters
 *
 ******************************************************************************/
#define RST_PIN  8
#define DC_PIN   9
#define CS_PIN   10
#define BUSY_PIN 7

/*******************************************************************************
 *
 * Commands
 *
 ******************************************************************************/
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

/*******************************************************************************
 *
 * Modes and parameters
 *
 ******************************************************************************/
// 0xF7
// - Enable clock signal
// - Enable Analog
// - Load temperature value
// - DISPLAY with DISPLAY Mode 1
// - Disable Analog
// - Disable OSC
#define DISPLAY_MODE_1 0xF7
// 0xF7
// - Enable clock signal
// - Enable Analog
// - Load temperature value
// - DISPLAY with DISPLAY Mode 2
// - Disable Analog
// - Disable OSC
#define DISPLAY_MODE_2 0xFF
// 0xB1
// - Enable clock signal
// - Load temperature value
// - Load LUT with DISPLAY Mode 1
// - Disable clock signal
#define LUT_DISPLAY_MODE_1 0xB1
#define LUT_DISPLAY_MODE_2 0xB9

enum DisplayMode {
    DisplayMode1 = DISPLAY_MODE_1,
    DisplayMode2 = DISPLAY_MODE_2,
};

class Waveshare_EPD {
    int16_t width, height;
    DisplayMode displayMode;

    public:
        Waveshare_EPD(int16_t, int16_t);
        ~Waveshare_EPD(void);
        void begin(void);
        void clear(void);
        void display(void);
        void displayModeFull(void);
        void displayModePartial(void);
        void reset(void);
        void sleep(void);
        void waitUntilIdle(void);
        void wake(void);
        void writeMemory(unsigned char *, int16_t, int16_t, int16_t, int16_t);

    private:
        void sendCommand(unsigned char);
        void sendData(unsigned char);
        void setMemoryArea(int, int, int, int);
        void setMemoryPointer(int, int);
        void spiTransfer(unsigned char);
};

#endif
