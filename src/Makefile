CC = gcc
STDFLAGS = -Wall -Werror -Wextra -std=c11
CFLAGS_DEV = -g -Wall -Werror -Wextra -std=c11
LINUX_FLAGS = -lsubunit -lrt -lpthread -lm
LIBS = -lcheck
VALGRIND_FLAGS=--trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all --verbose

SRC = $(wildcard modules/*.c)
OBJ = $(patsubst %.c, %.o, *.c)

PREF_TEST_SRC = ./tests/
TEST_SRC = $(wildcard $(PREF_TEST_SRC)/*.c)
GCOV_DIR = report
TARGET = s21_3DViewer_v1_0.a

OS := $(shell uname -s)

ifeq ($(OS),Linux)
  OPEN_CMD = xdg-open
  TEST_FLAGS = $(LIBS) $(LINUX_FLAGS)
endif
ifeq ($(OS),Darwin)
  OPEN_CMD = open
  TEST_FLAGS = $(LIBS)
endif

all: $(TARGET)

$(TARGET): ${SRC}
	$(CC) -c $(STDFLAGS) $(SRC)
	ar rc $@ $(OBJ)
	ranlib $@

install:
	rm -rf 3DViewer/build 3DViewer/third_party; \
	cd 3DViewer; \
	mkdir third_party; \
	cd third_party; \
	git clone https://github.com/tonitaga/QtGifImage.git; \
	cd -; \
	mkdir build; \
	(cd build && cmake ../); \
	(cd build && make); \
	
dist: install 
	cd 3DViewer/build
	tar --totals -cvf 3DViewer.tar 3DViewer/build/

dvi:
	doxygen Doxyfile
	open html/index.html

test: $(TARGET)
	${CC} $(STDFLAGS) ${TEST_SRC} $< -o unit_test $(TEST_FLAGS)
	./unit_test

gcov_report:
	make clean
	mkdir -p $(GCOV_DIR)
	$(CC) $(SRC) $(TEST_SRC) -o greport --coverage $(TEST_FLAGS)
	./greport
	lcov -t "s21_smart_calc" -o s21_smart_calc.info -c -d .
	genhtml -o ./$(GCOV_DIR) s21_smart_calc.info
	$(OPEN_CMD) ./report/index.html


valgrind: $(TARGET)
	$(CC) $(CFLAGS_DEV) ${TEST_SRC} $< -o test $(TEST_FLAGS)
	CK_FORK=no valgrind $(VALGRIND_FLAGS) --log-file=RESULT_VALGRIND.txt ./test

dev:
	$(CC) $(CFLAGS_DEV) $(SRC) $(LINUX_FLAGS)
	./a.out

style: clean
	cp ../materials/linters/.clang-format ../src/.clang-format
	clang-format -n modules/*.c modules/*.h  $(PREF_TEST_SRC)*.c 3DViewer/*.h 3DViewer/*.cpp
	rm .clang-format

uninstall:
	rm -rf 3DViewer/build
	rm -rf 3DViewer/third_party
	rm -rf ./3DViewer/build*

clean:
	rm -rf unit_test test greport html latex
	rm -rf RESULT_VALGRIND.txt
	rm -rf *.o *.a *.tar
	rm -rf *.gcda *.gcno *.info
	rm -rf s21_test report