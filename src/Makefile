CFLAGS := -std=c11 -pedantic
CPPFLAGS := -Wall -Werror -Wextra
CC = gcc
GFLAGS = --coverage
TFLAGS = -lcheck
OBJECTS = *.o
SOURCES := helpers/*.c

SOURCES_TEST := tests/s21_test.c 

all: clean test

3dViewer_1.a:
	@$(CC) $(CPPFLAGS) $(SOURCES) $(ASAN) -c
	@ar rcs 3dViewer_1.a $(OBJECTS)
	@rm *.o

test: 3dViewer_1.a $(SOURCES_TEST)
	$(CC) $(CPPFLAGS) $(SOURCES_TEST) 3dViewer_1.a -o test.out -lcheck -lm
	@./test.out

check:
	clang-format -n -style=Google $(SOURCES) $(SOURCES_TEST) helpers/*.c project/*.cpp project/*.h tests/s21_*
	clang-format -i -style=Google $(SOURCES) $(SOURCES_TEST) helpers/*.c project/*.cpp project/*.h tests/s21_*

leaks:
	CK_FORK=no leaks --atExit -- ./test

gcov_report:
	gcc -o test $(SOURCES_TEST) --coverage $(SOURCES) -lcheck -lm
	./test
	lcov -t "a.out" -o test.info -c -d .
	genhtml -o report test.info
	open ./report/index.html
	rm -rf test *.o *.a *gcda *gcno *info

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
	rm -rf html

dvi: doxygen
	open ../README_RUS.md
	open ./html/index.html

doxygen:
	doxygen

clean:
	rm -rf $(OBJECTS) 3dViewer_1.a test *.gcda *.gcno *.html *.css report/ user_guide/
	rm -rf *.exe
	rm -rf 3dViewer_1.exe
	rm -rf 3dViewer_1.app
	rm -rf 3dViewer_1.exe.pro
	rm -rf html

dist:
	cd .. && tar -czf SRC_C8_3dViewer_1.0-0.tgz src

download_models: 
	curl -L -o cow.obj 'https://docs.google.com/uc?export=download&id='1jlbWBA8PazRW_rkYjeORLePHmA2foAEI 
	curl -L -o Among%20US.obj 'https://docs.google.com/uc?export=download&id='1gN_mGEwYwlyiT0ggFFqxsrfAouFzK5FB
	curl -L -o cube_first.obj 'https://docs.google.com/uc?export=download&id='1HnXI9gkkPufPZlr1RFeWu_GQQir_CT29
	curl -L -o shuttle.obj 'https://docs.google.com/uc?export=download&id='1xKT6ep0xwtILr8LqNuvat8l1tVvSiNYp