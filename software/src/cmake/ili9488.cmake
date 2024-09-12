set(LCD_PIN_DB_BASE  0)  # 8080 LCD data bus base pin
set(LCD_PIN_DB_COUNT 8) # 8080 LCD data bus pin count
# set(LCD_PIN_CS  29)  # 8080 LCD chip select pin
set(LCD_PIN_WR  22)  # 8080 LCD write pin
set(LCD_PIN_RS  23)  # 8080 LCD register select pin
# set(LCD_PIN_RD  18)  # 8080 LCD read pin
set(LCD_PIN_RST 24)  # 8080 LCD reset pin
set(LCD_PIN_BL  21)  # 8080 LCD backlight pin
set(LCD_HOR_RES 480)
set(LCD_VER_RES 320)
set(DISP_OVER_PIO 1) # 1: PIO, 0: GPIO
set(PIO_USE_DMA   1)   # 1: use DMA, 0: not use DMA

if (LCD_PIN_DB_COUNT EQUAL 8)
    set(I80_BUS_WR_CLK_KHZ 80000)
elseif(LCD_PIN_DB_COUNT EQUAL 16)
    set(I80_BUS_WR_CLK_KHZ 50000)
else()
    message(FATAL_ERROR "LCD_PIN_DB_COUNT must be 8 or 16")
endif()

