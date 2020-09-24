MCU = atmega32u4
BOOTLOADER = atmel-dfu

OLED_DRIVER_ENABLE = yes   # Enables the use of OLED displays
ENCODER_ENABLE = yes       # Enables the use of one or more encoders
RGBLIGHT_ENABLE = yes      # Enable keyboard RGB underglow
SLEEP_LED_ENABLE = no

Link_Time_Optimization = yes # Reduce size of firmware by optimizing at link time
EXTRAFLAGS += -flto
