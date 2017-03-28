
BUILD_DIR := $(SRC_TOP)/../Build

CC := g++

CPPFLAGS := -Wall -Werror -std=c++11

ifdef RELEASE
CPPFLAGS +=  -O3 -DRELEASE
else
CPPFLAGS +=  -g3 -fPIC
endif

LDFLAGS += -Wall -g #-O2 

MODULES :=

SOFLAGS := -fPIC -shared

