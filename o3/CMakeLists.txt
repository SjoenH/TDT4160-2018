cmake_minimum_required(VERSION 3.12)
project(o3)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(o3
        build/bsp_stk.d
        build/bsp_stk.o
        build/bsp_stk_leds.d
        build/bsp_stk_leds.o
        build/bsp_trace.d
        build/bsp_trace.o
        build/em_assert.d
        build/em_assert.o
        build/em_cmu.d
        build/em_cmu.o
        build/em_emu.d
        build/em_emu.o
        build/em_gpio.d
        build/em_gpio.o
        build/em_lcd.d
        build/em_lcd.o
        build/em_rtc.d
        build/em_rtc.o
        build/em_system.d
        build/em_system.o
        build/em_usart.d
        build/em_usart.o
        build/em_vcmp.d
        build/em_vcmp.o
        build/init.d
        build/init.o
        build/o3.d
        build/o3.o
        build/segmentlcd.d
        build/segmentlcd.o
        build/startup_efm32gg.o
        build/system_efm32gg.d
        build/system_efm32gg.o
        build/vddcheck.d
        build/vddcheck.o
        exe/o3.bin
        exe/o3.out
        lst/o3.map
        CMakeLists.txt
        efm32gg.ld
        gpio.h
        Makefile
        o3.c
        o3.h
        o3.iml
        systick.h)
