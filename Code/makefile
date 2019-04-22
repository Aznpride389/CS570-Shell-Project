mush: command.o tokenizer.o
	g++ -o mush -g command.o tokenizer.o -lreadline;
	rm *.o
tokenizer.o: tokenizer.cpp tokenizer.h
	g++ -c tokenizer.cpp

command.o: command.cpp tokenizer.h
	g++ -c command.cpp

clean:
	rm -f *.o mush
