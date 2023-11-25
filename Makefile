log: log.c log.h
	clang log.c -o log.out

run: log
	./log.out

clean:
	rm -f *.out

