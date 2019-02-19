# Makefile

main.out: main.o fl_E2bus.o knl_E2bus.o
	gcc main.o fl_E2bus.o knl_E2bus.o -o main.out -lwiringPi

main.o: main.c
	gcc -c main.c

fl_E2bus.o: fl_E2bus.c
	gcc -c fl_E2bus.c

knl_E2bus.o: knl_E2bus.c
	gcc -c knl_E2bus.c
