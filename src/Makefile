CFLAGS := -std=c11 -pedantic
CPPFLAGS := -Wall -Werror -Wextra
CC = gcc
GFLAGS = --coverage
TFLAGS = -lcheck
OBJECTS = *.o
SOURCES := helpers/s21_*

SOURCES_TEST := 

all: clean test

3d_Viewer.a:
	@$(CC) $(CPPFLAGS) $(SOURCES) $(ASAN) -c
	@ar rcs 3d_Viewer.a $(OBJECTS)
	@rm *.o

test:
 echo "not done yet"

check:
	clang-format -n -style=Google $(SOURCES) $(SOURCES_TEST) helpers/s21_* project/*.c project/*.cpp project/*.h 

leaks:
	CK_FORK=no leaks --atExit -- ./test

gcov_report:
	@$(CC) $(CPPFLAGS) $(SOURCES) $(GFLAGS) $(ASAN) -c
	@ar rcs 3d_Viewer.a $(OBJECTS)
	@rm *.o
	@$(CC) $(CPPFLAGS) $(ASAN) $(GFLAGS) 3d_Viewer.a $(SOURCES_TEST) $(TFLAGS) $(VAR) -o test
	@./test
	lcov -t "test" -o test.info -c -d .
	genhtml -o report test.info
	open report/index.html

install:
 	mkdir build
	cd build&&qmake ../project/3d_Viewer.pro&&make&&mv 3d_Viewer.app ../3d_Viewer.app
	rm -R build
	open 3d_Viewer.app
	qmake -project project/3d_Viewer.pro -o 3d_Viewer.exe

uninstall:
	cd build && make clean
	rm -rf build/CMakeCache.txt build/*
	rm -r build

dvi:

clean:
	rm -rf $(OBJECTS) 3d_Viewer.a test *.gcda *.gcno *.html *.css report/ user_guide/
	rm -rf *.exe
	rm -rf 3d_Viewer.exe

dist:
	cd .. && tar -czf SRC_C8_3d_Viewer.0-0.tgz src