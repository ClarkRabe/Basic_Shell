mssh:	cscd340Lab8.c ./tokenize/makeArgs.o ./utils/myUtils.o ./process/process.o ./pipes/pipes.o ./aliasUtils/aliasUtils.o ./fileUtils/fileUtils.o ./history/history.o ./linkedList/LinkedList.o ./listUtils/listUtils.o ./redirect/redirect.o
	gcc -g cscd340Lab8.c ./tokenize/makeArgs.o ./utils/myUtils.o ./process/process.o ./pipes/pipes.o ./aliasUtils/aliasUtils.o ./fileUtils/fileUtils.o ./history/history.o ./linkedList/LinkedList.o ./listUtils/listUtils.o ./redirect/redirect.o -o mssh

makeArgs.o:	./tokenize/makeArgs.c ./tokenize/makeArgs.h
	gcc -g -c ./tokenize/makeArgs.c

myUtils.o:	./utils/myUtils.c ./utils/myUtils.h
	gcc -g -c ./utils/myUtils.c

process.o:	./process/process.c ./process/process.h
	gcc -g -c ./process/process.c	

pipes.o:	./pipes/pipes.c ./pipes/pipes.h
	gcc -g -c ./pipes/pipes.c

aliasUtils.o:	./aliasUtils/aliasUtils.c ./aliasUtils/aliasUtils.h
	gcc -g -c ./aliasUtils/aliasUtils.c

fileUtils.o:	./fileUtils/fileUtils.c ./fileUtils/fileUtils.h
	gcc -g -c ./fileUtils/fileUtils.c

history.o:	./history/history.c ./history/history.h
	gcc -g -c ./history/history.c

linkedList.o:	./linkedList/LinkedList.c ./linkedList/LinkedList.h
	gcc -g -c ./linkedList/LinkedList.c

listUtils.o:	./listUtils/listUtils.c ./listUtils/listUtils.h
	gcc -g -c ./listUtils/listUtils.c

redirect.o:	./redirect/redirect.c ./redirect/redirect.h
	gcc -g -c ./redirect/redirect.c


clean:
	rm ./pipes/pipes.o	
	rm ./utils/myUtils.o
	rm ./process/process.o
	rm ./tokenize/makeArgs.o
	rm ./aliasUtils/aliasUtils.o
	rm ./fileUtils/fileUtils.o
	rm ./history/history.o
	rm ./linkedList/LinkedList.o
	rm ./listUtils/listUtils.o
	rm ./redirect/redirect.o
	rm lab8

