CC = gcc
CFLAGS = -c -Wall -Wextra -Werror

s21_cat: cat.o
	$(CC) cat.o -o s21_cat

cat.o: cat.c
	$(CC) $(CFLAGS) cat.c

test: s21_cat
	./s21_cat test_file1.txt test_file2.txt test_file3.txt test_file4.txt
	./s21_cat -e test_file1.txt test_file2.txt test_file3.txt test_file4.txt
	./s21_cat -b test_file1.txt test_file2.txt test_file3.txt test_file4.txt
	./s21_cat -n test_file1.txt test_file2.txt test_file3.txt test_file4.txt
	./s21_cat -t test_file1.txt test_file2.txt test_file3.txt test_file4.txt
	./s21_cat -s test_file1.txt test_file2.txt test_file3.txt test_file4.txt

	

rebuild: clear s21_cat


clear:
	rm -rf *.o s21_cat 