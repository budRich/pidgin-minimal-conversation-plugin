CC ?= gcc
CFLAGS += -O2 -Werror -Wall -Wextra -Wno-missing-braces \
          -Wno-missing-field-initializers -Wformat=2 -Wswitch-default \
          -Wswitch-enum -Wcast-align -Wpointer-arith -Wbad-function-cast \
          -Wstrict-overflow=5 -Winline -Wundef -Wnested-externs \
          -Wshadow -Wunreachable-code -Wlogical-op -Wfloat-equal \
          -Wstrict-aliasing=2 -Wredundant-decls \
          -Wold-style-definition -Wno-unused-parameter -std=c99 \
          -Wno-error=deprecated-declarations \
          `pkg-config --cflags glib-2.0 gtk+-2.0 pidgin`


LDFLAGS += `pkg-config --libs glib-2.0 gtk+-2.0 pidgin`

ifdef PREFIX
  PLUGIN_DIR := $(PREFIX)/lib/purple-2
else
  PLUGIN_DIR := $(HOME)/.purple/plugins
endif

minimal_conversation.so: minimal_conversation.o
	$(CC) $(LDFLAGS) -shared $? -o $@ 

minimal_conversation.o: minimal_conversation.c
	$(CC) $(CFLAGS) -fPIC -c $< -o $@

clean:
	rm -f minimal_conversation.so
	rm -f *.o

install: minimal_conversation.so
	install -D -m755 $< $(DESTDIR)$(PLUGIN_DIR)/minimal_conversation.so

uninstall:
	rm $(DESTDIR)$(PLUGIN_DIR)/minimal_conversation.so
