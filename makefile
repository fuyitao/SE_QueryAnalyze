CC = g++
CFLAGS = -lstdc++ -std=c++0x -O2
INCLUDES = -I./seg_include
LIBS = -L./seg_lib -lccode -lsegmenter -luldict -lwordselecter -lullib -lpthread

objects = main.o utf8_to_char.o tool_function.o word_segment.o TransCode.o QueryPreprocess.o Synonym_Termweight.o

main: $(objects)
	$(CC) -o main $(objects) $(CFLAGS) $(LIBS) $(INCLUDES)

main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp

utf8_to_char.o: utf8_to_char.cpp
	$(CC) -c utf8_to_char.cpp

tool_function.o: tool_function.cpp
	$(CC) $(CFLAGS) -c tool_function.cpp

word_segment.o: word_segment.cpp
	$(CC) $(CFLAGS) -c word_segment.cpp

TransCode.o: seg_include/TransCode.c
	$(CC) -c seg_include/TransCode.c

QueryPreprocess.o: QueryPreprocess.cpp
	$(CC) $(CFLAGS) -c QueryPreprocess.cpp

Synonym_Termweight.o: Synonym_Termweight.cpp
	$(CC) $(CFLAGS) -c Synonym_Termweight.cpp

clean:
	rm *.o
