# Customize below to fit your system

# paths
PREFIX = /usr/local

# libs
LIBS = -lm

# flags
CFLAGS   = -std=c99 -pedantic -Wall -Wno-deprecated-declarations -Os
LDFLAGS  = ${LIBS}

# compiler and linker
CC = cc
