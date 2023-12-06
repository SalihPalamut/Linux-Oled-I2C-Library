SHELL = /bin/sh
CC = g++
LIBS  = 
CFLAGS +=  -Wall -Wextra
CFLAGS += -I. -ISSD1306Driver/ -ILinux-Oled-GFX-Library/

OBJS =  main.o Linux-Oled-GFX-Library/Linux_GFX.o SSD1306Driver/SSD1306.o

Oled:${OBJS}
	${CC} ${CFLAGS} ${OBJS} -o $@  ${LIBS}
	
clean:
	rm -rf *.o Linux-Oled-GFX-Library/*.o SSD1306Driver/*.o Oled

R:clean
R:CFLAGS +=-O3
R:Oled


Rd:clean
Rd:CFLAGS += -DDebug -g -O0
Rd:Oled

# DO NOT DELETE
