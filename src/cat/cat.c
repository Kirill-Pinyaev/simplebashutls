#include <stdio.h>
#include <stdlib.h>

#define SIZE 1024

void vivod(int argc, char **argv, int flag);
void f_e(FILE *fp);
void f_n(FILE *fp);
void f_b(FILE *fp);
void f_s(FILE *fp);
void f_t(FILE *fp);
void check(int argc, char **argv);
int in(char *list, char simv, int len);

int main(int argc, char **argv) { check(argc, argv); }

void vivod(int argc, char **argv, int flag) {
  char flags[flag + 1];
  for (int i = 0; i < flag + 1; i++) {
    flags[i] = argv[i][1];
  }
  for (int i = 1 + flag; i < argc; i++) {
    char s[SIZE];
    FILE *fp;
    fp = fopen(argv[i], "r");

    if (!fp) {
      printf("cat: %s: No such file or directory\n", argv[i]);
    } else {
      if (flag == 0) {
        while (fgets(s, SIZE, fp)) printf("%s", s);
      } else {
        if (in(flags, 'e', flag + 1)) {
          f_e(fp);
        }
        if (in(flags, 'n', flag + 1)) {
          f_n(fp);
        }
        if (in(flags, 'b', flag + 1)) {
          f_b(fp);
        }
        if (in(flags, 's', flag + 1)) {
          f_s(fp);
        }
        if (in(flags, 't', flag + 1)) {
          f_t(fp);
        }
      }
      fclose(fp);
    }
  }
}

void check(int argc, char **argv) {
  int flag = 0;
  while (argv[flag + 1][0] == '-') {
    flag++;
  }
  vivod(argc, argv, flag);
}

void f_b(FILE *fp) {
  char s[SIZE];
  int i = 1;
  while (fgets(s, SIZE, fp)) {
    if (s[0] != '\n') {
      printf("     %d ", i);
      i++;
    }
    printf("%s", s);
  }
}

void f_e(FILE *fp) {
  char s[SIZE];
  while (fgets(s, SIZE, fp)) {
    int i = 0;
    while (s[i] != 0) {
      if (s[i] == '\n') {
        printf("$");
      }
      printf("%c", s[i]);
      i++;
    }
  }
}
void f_n(FILE *fp) {
  char s[SIZE];
  int i = 1;
  while (fgets(s, SIZE, fp)) {
    printf("     %d ", i);
    printf("%s", s);
    i++;
  }
}

void f_s(FILE *fp) {
  char s[SIZE];
  int i = 0;
  while (fgets(s, SIZE, fp)) {
    if (s[0] == '\n') {
      if (i == 0) {
        printf("%s", s);
        i = 1;
      }
    } else {
      printf("%s", s);
      i = 0;
    }
  }
}

void f_t(FILE *fp) {
  char s[SIZE];
  while (fgets(s, SIZE, fp)) {
    int i = 0;
    while (s[i] != 0) {
      if (s[i] == ' ' && s[i + 1] == ' ' && s[i + 2] == ' ' &&
          s[i + 3] == ' ') {
        printf("^I");
        i += 4;
      } else {
        printf("%c", s[i]);
        i++;
      }
    }
  }
}

int in(char *list, char simv, int len) {
  int ret = 0;
  for (int i = 0; i < len; i++) {
    if (simv == list[i]) {
      ret = 1;
    }
  }
  return ret;
}
