/*
	reorder.c
		reorders data from main.F-output for easier access
		e.g. with gnuplot
		this file is part of FormCalc
		last modified 29 Oct 04 th

Syntax: reorder var1 var2 var3... < infile > outfile

For example, if you have the following source file

# MH = 300.00000
# MT = 175.00000
data1

# MH = 300.00000
# MT = 150.00000
data2

# MH = 350.00000
# MT = 175.00000
data3

# MH = 350.00000
# MT = 150.00000
data4

the output from running "reorder MH" will be

# MT = 175.00000
300.00000  data1
350.00000  data3

# MT = 150.00000
300.00000  data2
350.00000  data4

*/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/* to compile with a non-gnu cc, set the following to fixed values */
#define ARGC argc

#define BLOCK 10240
#define LINE 512

#define Allocate(p, n) \
  if( (p = malloc((n)*sizeof(*p))) == NULL ) { \
    fprintf(stderr, "Out of memory in " __FILE__ " line %d.\n", __LINE__); \
    exit(1); \
  }

#define Reallocate(p, n) \
  if( (p = realloc(p, (n)*sizeof(*p))) == NULL ) { \
    fprintf(stderr, "Out of memory in " __FILE__ " line %d.\n", __LINE__); \
    exit(1); \
  }

typedef struct group {
  struct group *next;
  char *para, *data;
  int pos, size;
} Group;


int main(int argc, char **argv)
{
  enum { Undefined, Comment, Data } state = Undefined;
  int warn[ARGC];
  char *para[ARGC];
  char prefix[2*LINE];
  char comment[BLOCK], *c;
  Group *anchor = NULL, *cur;
  int plen;

  if( argc < 2 ) {
    fprintf(stderr, "Usage:  %s para1 para2 ... < infile > outfile\n\n"
      "Reorders data files produced with FormCalc utilities by moving\n"
      "parameter values from the headers into the data columns.  Most\n"
      "plotting utilites can then easily plot the data vs. a parameter.\n\n",
      argv[0]);
    exit(1);
  }

  memset(warn, 0, sizeof(warn));
  *comment = 0;

  while( !feof(stdin) ) {
    char line[LINE];
    int len;

    *line = 0;
    fgets(line, sizeof(line), stdin);

    if( *line == '#' ) {
      char var[128];
      int i, n;

      if( state != Comment ) {
        memset(para, 0, sizeof(para));
        *comment = 0;
        c = comment;
        state = Comment;
      }

      n = -1;
      sscanf(line + 1, " %[^= ] =%n", var, &n);
      if( n > 0 ) {
        for( i = 1; i < argc; ++i )
          if( strcmp(var, argv[i]) == 0 ) {
            para[i] = strdup(line + 1 + n);
            goto loop;
          }

        c = memccpy(c, line, '\n', sizeof(line));
      }
      continue;
    }

    if( line[strspn(line, " \t\n")] == 0 ) {
      *comment = 0;
      state = Undefined;
      continue;
    }

    if( state != Data ) {
      Group **parent;

      char *p = prefix;
      if( state == Comment ) {
        int i;
        for( i = 1; i < argc; ++i )
          if( para[i] ) {
            p = memccpy(p, para[i], '\n', sizeof(prefix)) - 1;
            free(para[i]);
          }
          else if( !warn[i] ) {
            fprintf(stderr, "Warning: parameter %s not found\n", argv[i]);
            warn[i] = 1;
          }
      }
      *p = 0;
      plen = (int)(p - prefix) + 1;

      for( parent = &anchor; (cur = *parent); parent = &cur->next )
        if( strcmp(cur->para, comment) == 0 ) break;
      if( cur == NULL ) {
        Allocate(cur, 1);
        *parent = cur;
        cur->next = NULL;
        cur->para = strdup(comment);
        Allocate(cur->data, BLOCK);
        cur->pos = 0;
        cur->size = BLOCK;
      }

      state = Data;
    }

    len = cur->pos + plen + strlen(line);
    if( len > cur->size ) {
      do cur->size += BLOCK; while( len > cur->size );
      Reallocate(cur->data, cur->size);
    }
    cur->pos += sprintf(cur->data + cur->pos, "%s %s", prefix, line);

loop: ;
  }

  for( cur = anchor; cur; cur = cur->next )
    printf("%s%s\n\n", cur->para, cur->data);

  return 0;
}

