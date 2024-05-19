CC=gcc
CFLAGS=-Wall -Wextra -std=c99

# Lista de archivos adicionales
ADDITIONAL_FILES=Manufactura.c Mundo.c Robot.c

all: FactoryOfNumbers

FactoryOfNumbers: FactoryOfNumbers.c $(ADDITIONAL_FILES)
	$(CC) $(CFLAGS) -o FactoryOfNumbers FactoryOfNumbers.c $(ADDITIONAL_FILES)

clean:
	rm -f FactoryOfNumbers



