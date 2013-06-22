CC=gcc
CFLAGS=-I/home/bubble/mail/include -I/home/bubble/mail/lib/glib/include -I/home/bubble/mail/include/gtk-1.2 -I/home/bubble/mail/include/glib-1.2
DEPS = 
OBJ = socket.o main.o 

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

bmail: $(OBJ)
	gcc -o $@ $^ $(CFLAGS) -L/home/bubble/mail/lib/ -lgtk -lgdk -lgmodule -lglib -ldl -lXext -lX11 -lm


clean:
	rm -f *.o bmail
