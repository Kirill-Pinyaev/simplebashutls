CC = gcc
CFLAGS = -c -Wall -Wextra -Werror

s21_grep: grep.o
	$(CC) grep.o -o s21_grep -lpcre

grep.o: grep.c
	$(CC) $(CFLAGS) grep.c -lpcre

test: s21_grep
	./s21_grep ds test_file1.txt test_file2.txt test_file3.txt test_file4.txt
	./s21_grep -h ds test_file1.txt test_file2.txt test_file3.txt test_file4.txt
	./s21_grep [1-5] test_file1.txt test_file2.txt test_file3.txt test_file4.txt
	./s21_grep -i DS test_file1.txt test_file2.txt test_file3.txt test_file4.txt
	./s21_grep -v ds test_file1.txt test_file2.txt test_file3.txt test_file4.txt
	./s21_grep -c ds test_file1.txt test_file2.txt test_file3.txt test_file4.txt
	./s21_grep -l  ds *.txt
	./s21_grep -n ds test_file1.txt test_file2.txt test_file3.txt test_file4.txt
	./s21_grep -s -i ds test_file2.txt test_file5.txt
	./s21_grep -o sa test_file1.txt 
	./s21_grep -o sd test_file2.txt 
	./s21_grep -o dsf test_file3.txt 
	./s21_grep -o fsd test_file4.txt
	./s21_grep -f test_file_pattern.txt test_file1.txt test_file2.txt test_file3.txt test_file4.txt
	./s21_grep -e sg -e ds -e sf test_file1.txt test_file2.txt test_file3.txt test_file4.txt
    

rebuild: clear s21_grep


clear:
	rm -rf *.o s21_grep