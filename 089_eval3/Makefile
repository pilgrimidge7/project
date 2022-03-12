CFLAGS=-std=gnu++11 -pedantic -Wall -Werror -ggdb3
PROGS=cyoa-step1 cyoa-step2 cyoa-step3 cyoa-step4
OBJS=$(patsubst %,%.o,$(PROGS)) story.o page.o exception.o
all: $(PROGS)
cyoa-step%: cyoa-step%.o Story.o page.o exception.o
	g++ -o $@ $^
%.o: %.cpp
	g++ $(CFLAGS) -c $<

.PHONY: clean
clean:
	rm -f *~ $(PROGS) $(OBJS)

story.o: Story.hpp
page.o: page.hpp
exception.o: exception.hpp


