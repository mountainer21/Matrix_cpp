CC=g++
SRC=s21_matrix_oop.cc
OBJ=s21_matrix_oop.o
CFLAGS= -g -Wall -Werror -Wextra -std=c++17
TESTFLAGS=-lgtest -lpthread

all: s21_matrix_oop.a test

s21_matrix_oop.a:
	$(CC) $(CFLAGS) $(SRC) -c
	ar -rcs s21_matrix_oop.a $(OBJ)

test: s21_matrix_oop.a
	$(CC) $(CFLAGS) test.cc s21_matrix_oop.a -o test.out $(TESTFLAGS)
	./test.out

gcov_report:
	$(CC) test.cc -c
	$(CC) --coverage  s21_matrix_oop.cc  test.o -o test.out $(TESTFLAGS)
	./test.out
	lcov -t "test" -o test.info -c -d ./
	genhtml -o report test.info
	open report/index.html

clean:
	rm -rf *.out *.o s21_matrix_oop.a *.gcda *.gcno *.info 
	-rm -rf report

clang:
	cp ../materials/linters/.clang-format ./
	clang-format -i *.h *.cc
	clang-format -n *.h *.cc

