#include <ctype.h>
#include <pcre.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 1024

void check(int argc, char **argv);
void vivod(int argc, char **argv, int flag, char **matr_e, int count_e);
void f_i(FILE *fp, char *strok, char *file, int flag_h);
void f_v(FILE *fp, char *strok, char *file, int flag_h);
void f_c(FILE *fp, char *strok, char *file, int flag_h);
void f_l(FILE *fp, char *strok, char *file);
void f_n(FILE *fp, char *strok, char *file, int flag_h);
void f_o(FILE *fp, char *strok, char *file, int flag_h);
void f_f(FILE *fp, char *namefile, char *file, int flag_h);
void f_e(FILE *fp, char **strok, int count_e, char *file, int flag_h);
void serch_p(FILE *fp, char *strok, char *file, int flag_h);
int in(char *list, char simv, int len);
int serchpcre(char *strok, char *vvodstrok, int flag, char *file);

int main(int argc, char **argv) { check(argc, argv); }

void check(int argc, char **argv) {
  int flag = 0;
  char **matr_e;
  int i = 0;
  matr_e = malloc(SIZE * sizeof(char));
  while (argv[flag + 1][0] == '-' || argv[flag + 2][0] == '-') {
    if (argv[flag + 1][1] == 'e') {
      int lenn = strlen(argv[flag + 2]);
      matr_e[i] = malloc(lenn * sizeof(char));
      for (int j = 0; j < lenn; j++) {
        matr_e[i][j] = argv[flag + 2][j];
      }
      i++;
    }
    flag++;
  }
  vivod(argc, argv, flag, matr_e, i);
}

void vivod(int argc, char **argv, int flag, char **matr_e, int count_e) {
  char flags[flag + 1];
  for (int i = 0; i < flag + 1; i++) {
    flags[i] = argv[i][1];
  }
  int flag_h = 1;
  for (int i = 2 + flag; i < argc; i++) {
    if (in(flags, 'h', flag + 1) || (argc - 2 - flag) == 1) {
      flag_h = 0;
    }
    FILE *fp;
    fp = fopen(argv[i], "r");

    if (!fp) {
      if (in(flags, 's', flag + 1) == 0) {
        printf("grep: %s: No such file or directory\n", argv[i]);
      }
      continue;
    } else {
      if (flag == 0 || (flag == 1 && in(flags, 'h', flag + 1))) {
        serch_p(fp, argv[1 + flag], argv[i], flag_h);
      } else {
        if (in(flags, 'i', flag + 1)) {
          f_i(fp, argv[1 + flag], argv[i], flag_h);
        }
        if (in(flags, 'v', flag + 1)) {
          f_v(fp, argv[1 + flag], argv[i], flag_h);
        }
        if (in(flags, 'c', flag + 1)) {
          f_c(fp, argv[1 + flag], argv[i], flag_h);
        }
        if (in(flags, 'n', flag + 1)) {
          f_n(fp, argv[1 + flag], argv[i], flag_h);
        }
        if (in(flags, 'o', flag + 1)) {
          f_o(fp, argv[1 + flag], argv[i], flag_h);
        }
        if (in(flags, 'f', flag + 1)) {
          f_f(fp, argv[1 + flag], argv[i], flag_h);
        }
        if (in(flags, 'e', flag + 1)) {
          f_e(fp, matr_e, count_e, argv[i], flag_h);
        }
        if (in(flags, 'l', flag + 1)) {
          f_l(fp, argv[1 + flag], argv[i]);
        }
      }
      fclose(fp);
    }
  }
  if (count_e != 0) {
    for (int j = 0; j < count_e; j++) {
      free(matr_e[j]);
    }
  }
  free(matr_e);
}

void serch_p(FILE *fp, char *strok, char *file, int flag_h) {
  char s[SIZE];
  while (fgets(s, SIZE, fp)) {
    if (serchpcre(strok, s, 1, file)) {
      if (flag_h) {
        printf("%s: %s", file, s);
      } else {
        printf("%s", s);
      }
    }
  }
}

void f_i(FILE *fp, char *strok, char *file, int flag_h) {
  char s[SIZE];
  while (fgets(s, SIZE, fp)) {
    int i = 0;
    char s_2[SIZE];
    while (s[i] != 0 || s_2[i] != 0) {
      s_2[i] = s[i];
      s[i] = tolower(s[i]);
      i++;
    }
    i = 0;
    while (strok[i] != 0) {
      strok[i] = tolower(strok[i]);
      i++;
    }
    if (serchpcre(strok, s, 1, file)) {
      if (flag_h) {
        printf("%s: %s", file, s_2);
      } else {
        printf("%s", s_2);
      }
    }
  }
}

void f_v(FILE *fp, char *strok, char *file, int flag_h) {
  char s[SIZE];
  while (fgets(s, SIZE, fp)) {
    if (!serchpcre(strok, s, 1, file)) {
      if (flag_h) {
        printf("%s: %s", file, s);
      } else {
        printf("%s", s);
      }
    }
  }
}

void f_c(FILE *fp, char *strok, char *file, int flag_h) {
  char s[SIZE];
  int count = 0;
  while (fgets(s, SIZE, fp)) {
    if (serchpcre(strok, s, 1, file)) {
      count++;
    }
  }
  if (flag_h) {
    printf("%s: %d\n", file, count);
  } else {
    printf("%d\n", count);
  }
}

void f_n(FILE *fp, char *strok, char *file, int flag_h) {
  char s[SIZE];
  int count = 0;
  while (fgets(s, SIZE, fp)) {
    count++;
    if (serchpcre(strok, s, 1, file)) {
      if (flag_h) {
        printf("%s:%d: %s", file, count, s);
      } else {
        printf("%d: %s", count, s);
      }
    }
  }
}

void f_l(FILE *fp, char *strok, char *file) {
  char s[SIZE];
  while (fgets(s, SIZE, fp)) {
    if (serchpcre(strok, s, 1, file)) {
      printf("%s\n", file);
      break;
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

void f_o(FILE *fp, char *strok, char *file, int flag_h) {
  char s[SIZE];
  while (fgets(s, SIZE, fp)) {
    if (flag_h) {
      serchpcre(strok, s, 3, file);
    } else {
      serchpcre(strok, s, 2, file);
    }
  }
}

void f_f(FILE *fp, char *namefile, char *file, int flag_h) {
  char s[SIZE];
  char s2[SIZE];

  FILE *fp2;
  while (fgets(s, SIZE, fp)) {
    fp2 = fopen(namefile, "r");
    if (!fp2) {
      printf("grep: %s: No such file or directory\n", namefile);
      break;
    }
    while (fgets(s2, SIZE, fp2)) {
      int i = 0;
      char *s2_exit;
      s2_exit = malloc(strlen(s2) * sizeof(char));
      while (s2[i] != '\n') {
        s2_exit[i] = s2[i];
        i++;
      }
      if (serchpcre(s2_exit, s, 1, file)) {
        if (flag_h) {
          printf("%s: %s", file, s);
        } else {
          printf("%s", s);
        }
        free(s2_exit);
        break;
      }
      free(s2_exit);
    }
    fclose(fp2);
  }
}

void f_e(FILE *fp, char **strok, int count_e, char *file, int flag_h) {
  char s[SIZE];
  while (fgets(s, SIZE, fp)) {
    for (int i = 0; i < count_e; i++) {
      if (serchpcre(strok[i], s, 1, file)) {
        if (flag_h) {
          printf("%s: %s", file, s);
        } else {
          printf("%s", s);
        }
        break;
      }
    }
  }
}

int serchpcre(char *strok, char *vvodstrok, int flag, char *file) {
  int ret = 0;
  pcre *pc;
  const char *error;
  int erroffset;
  int re;
  int ovector[30];
  const char *substring;
  const char *regex = strok;
  const char *subject = vvodstrok;
  pc = pcre_compile(regex, 0, &error, &erroffset, NULL);
  int startoffsed = 0;
  while (1) {
    re = pcre_exec(pc, NULL, subject, strlen(subject), startoffsed, 0, ovector,
                   30);
    if (re == PCRE_ERROR_NOMATCH) {
      break;
    } else {
      startoffsed = ovector[1];
      for (int i = 0; i < re; i++) {
        pcre_get_substring(subject, ovector, re, i, &substring);
        if (flag == 1) {
          ret = 1;
        }
        if (flag != 1) {
          if (flag == 2) {
            printf("%s\n", substring);
          } else {
            printf("%s:%s\n", file, substring);
          }
        }
        pcre_free_substring(substring);
      }
    }
  }
  pcre_free(pc);
  return ret;
}