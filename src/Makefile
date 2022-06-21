all: main.o gomoku.o
	gcc -o cbb107041 main.o gomoku.o

main.o: main.c main.h
	gcc -c main.c

gomoku.o: gomoku.c gomoku.h main.h
	gcc -c gomoku.c


clean:
	rm -rf *.o *.*~ a.out *~ chessboard chessboard2 log pklog position cbb107041
