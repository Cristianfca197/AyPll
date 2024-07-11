# Flags de gcc. Se usan automáticamente para compilar *.c → *.o
CFLAGS := -g -std=c99 -Wall -Wformat=2
CFLAGS += -Wshadow -Wpointer-arith -Wunreachable-code
CFLAGS += -Wconversion -Wno-sign-conversion -Wbad-function-cast

# Se pueden comentar durante el desarrollo.
CFLAGS += -Werror

# Si se ejecuta `make` a secas, se compilarán prom_movil.o, fixcol, filesplit y strutil.o .
#
# También se puede invocar `make fixcol`, `make filesplit` o `make strutil.o` para
# compilar una parte del TP solamente.

all: fixcol filesplit strutil.o prom_movil.o

include deps.mk
