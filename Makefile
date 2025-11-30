# NOTE!
# THE BELOW CODE IS MADE FOR WINDOWS DISTRIBUTIONS 

# ------------------------------------------------------------------
# Paths – change only if your MinGW installation lives somewhere else
# ------------------------------------------------------------------

INC_DIR  = C:/MinGW/include
LIB_DIR  = C:/MinGW/lib
# ------------------------------------------------------------------
# Tools & flags
# ------------------------------------------------------------------
CC = gcc
CFLAGS = -O2 -Wall -Wextra -std=c99
# -shared creates the DLL
# -Wl,--out-implib,librc4.a tells the linker to also produce an import lib
LDFLAGS = -shared -Wl,--out-implib,librc4.a

# ------------------------------------------------------------------
# Public targets
# ------------------------------------------------------------------
.PHONY: all clean install

# Default: build the DLL and a tiny demo exe (main.exe)
all: RC4.dll main.exe

# --------------------------------------------------------------
# Build the shared library
# --------------------------------------------------------------
RC4.dll: RC4.o
	$(CC) $(LDFLAGS) -o $@ $^
	
# Compile the library source into an object file
RC4.o: RC4.c RC4.h
	$(CC) $(CFLAGS) -c -o $@ $<

# --------------------------------------------------------------
# Optional tiny demo program (shows the DLL works)
# --------------------------------------------------------------
main.exe: main.o librc4.a
	$(CC) -o $@ $< -L. -lrc4
	
main.o: main.c RC4.h
	$(CC) $(CFLAGS) -c -o $@ $<
	
# The import library is generated automatically when the DLL is built,
# but we list it as a target so make knows it exists.
librc4.a: RC4.dll

# --------------------------------------------------------------
# House-keeping
# --------------------------------------------------------------
clean:
	-del /Q *.o *.dll *.exe librc4.a
# --------------------------------------------------------------
# Install the public artifacts into your MinGW tree
# --------------------------------------------------------------
install: RC4.dll librc4.a RC4.h
	copy RC4.dll $(LIB_DIR)
	copy librc4.a $(LIB_DIR)
	copy RC4.h $(INC_DIR)


# NOTE!
# THE BELLOW CODE IS THE MAKE FILE FOR LINUX BASED DISTRIBUTIONS
# NEEDS TO BE RUN WITH SUDO ACCESS TO INSTALL LIBRARY


# incdir = /usr/include
# libdir = /usr/lib/x86_64-linux-gnu

# all: RC4 main

# main: main.o
# 	gcc main.o -o main -O2 -Wall 

# main.o: main.c
# 	gcc -c -O2 -Wall main.c

# RC4: RC4.o
# 	gcc RC4.o -o RC4.so -O2 -Wall -fPIC -shared -ldl -D_GNU_SOURCE
	

# RC4.o: RC4.c
# 	gcc -c -O2 -Wall RC4.c 

# clean:
# 	rm -f *.o *.so main

# install:	
# 	cp RC4.so ${libdir}
# 	cp RC4.h ${incdir}
# 	ldconfig