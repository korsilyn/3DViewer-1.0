CFLAGS := -std=c11 -pedantic
CPPFLAGS := -Wall -Werror -Wextra
CC = gcc
GFLAGS = --coverage
TFLAGS = -lcheck
OBJECTS = *.o
SOURCES := helpers/s21_*

SOURCES_TEST := 

all: clean test

3dViewer_1.a:
	@$(CC) $(CPPFLAGS) $(SOURCES) $(ASAN) -c
	@ar rcs 3dViewer_1.a $(OBJECTS)
	@rm *.o

test:
	echo "not done yet"

check:
	clang-format -n -style=Google $(SOURCES) $(SOURCES_TEST) helpers/s21_* project/*.c project/*.cpp project/*.h 

leaks:
	CK_FORK=no leaks --atExit -- ./test

gcov_report:
	@$(CC) $(CPPFLAGS) $(SOURCES) $(GFLAGS) $(ASAN) -c
	@ar rcs 3dViewer_1.a $(OBJECTS)
	@rm *.o
	@$(CC) $(CPPFLAGS) $(ASAN) $(GFLAGS) 3dViewer_1.a $(SOURCES_TEST) $(TFLAGS) $(VAR) -o test
	@./test
	lcov -t "test" -o test.info -c -d .
	genhtml -o report test.info
	open report/index.html

install:
	mkdir build
	cd build&&qmake ../project/3dViewer_1.pro&&make&&mv 3dViewer_1.app ../3dViewer_1.app
	rm -rf build
	open 3dViewer_1.app
	qmake -project project/3dViewer_1.pro -o 3dViewer_1.exe

uninstall:
	# cd build && make clean
	# rm -rf build/CMakeCache.txt build/*
	rm -rf build
	rm -rf 3dViewer_1.exe
	rm -rf 3dViewer_1.pro.user
	rm -rf 3dViewer_1.pro

dvi:
	open ../README_RUS.md

doxygen:
	

clean:
	rm -rf $(OBJECTS) 3dViewer_1.a test *.gcda *.gcno *.html *.css report/ user_guide/
	rm -rf *.exe
	rm -rf 3dViewer_1.exe
	rm -rf 3dViewer_1.app
	rm -rf 3dViewer_1.exe.pro

dist:
	cd .. && tar -czf SRC_C8_3dViewer_1.0-0.tgz src