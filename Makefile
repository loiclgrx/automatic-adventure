OBJECTS = symbol.o init.o error.o main.o language.tab.o lex.yy.o
SOURCES = symbol.cpp init.cpp error.cpp main.cpp language.tab.cpp lex.yy.cpp
EXE = infix2postfix
CFLAGS += -Wall -g

$(EXE):	$(OBJECTS)
	g++ $(CFLAGS) -o $(EXE) $(OBJECTS)

main.o: 	main.cpp global.hpp language.tab.hpp
	g++ $(CFLAGS) -c main.cpp

lexer.o: 	lexer.cpp global.hpp language.tab.hpp
	g++ $(CFLAGS) -c lexer.cpp

emitter.o: 	emitter.cpp global.hpp language.tab.hpp
	g++ $(CFLAGS) -c emitter.cpp

parser.o:   parser.cpp global.hpp language.tab.hpp
	g++ $(CFLAGS) -c parser.cpp

symbol.o: 	symbol.cpp global.hpp language.tab.hpp
	g++ $(CFLAGS) -c symbol.cpp

init.o: 	init.cpp global.hpp language.tab.hpp
	g++ $(CFLAGS) -c init.cpp

error.o: 	error.cpp global.hpp language.tab.hpp
	g++ $(CFLAGS) -c error.cpp

language.tab.cpp language.tab.hpp: language.ypp
	bison -d language.ypp

lex.yy.cpp: language.l
	flex language.l ; mv lex.yy.c lex.yy.cpp
clean: 
	rm -f $(EXE) $(OBJECTS) 29.tar.gz 29.zip language.tab.cpp language.tab.hpp lex.yy.cpp lex.yy.o *~

archives: clean
	cd ..; rm 29.tar 29.zip 29/29.tar 29/29.zip; tar -cvf 29.tar 29; gzip -9 29.tar; zip -r 29.zip 29; mv 29.zip 29/29.zip; mv 29.tar.gz 29/29.tar.gz
