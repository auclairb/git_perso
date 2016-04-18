CC = gcc
CFLAGS = -g -Wall
OBJ1 = Serv_UDP.o
OBJ2 = Client_UDP.o

serveur : $(OBJ1)
	  $(LINK.o) $^ $(LOADLIBES) $(LDLIBS) -o $@

client : $(OBJ2)
	$(LINK.o) $^ $(LOADLIBES) $(LDLIBS) -o $@
clean : 
	rm -f $(OBJS)
	rm -f serveur client
	rm -f *~
	rm -f *.o
.phony: clean
