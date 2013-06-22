#!/bin/sh

gcc `/home/bubble/mail/bin/gtk-config --cflags` -c *.c
gcc -o bmail *.o `/home/bubble/mail/bin/gtk-config --libs`
