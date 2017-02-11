TARGET := main
SOURCES := main.cpp glcd/gText.cpp glcd/glcd.cpp glcd/glcd_Device.cpp
CPPFLAGS := -I ./glcd -Wp,-w
BOARD := uno
BOARD_BUILD_FCPU := 8000000
include arduino.mk
