#ifndef INTERFACE
#define INTERFACE

#define DEFAULT_B 32 * BUFSIZ /* default buffer size */

/* define argument container */
typedef struct args{
  char  h;  /* help message? */
  char  v;  /* version message? */
  char  e;  /* error message? */
  char  p;  /* postscript output */
  char *s;  /* plot size */
  char  N;  /* no ticks */
  char  d;  /* dots? */
  char  c;  /* print command and exit */
  char  P;  /* linespoints? */
  char  l;  /* log scale? */
  char *t;  /* title */
  char  D;  /* dumb terminal? */
  float w;  /* width of plot */
  char *X;  /* x-range */
  char *Y;  /* y-range */
  char *x;  /* x-label */
  char *y;  /* y-label */
  char **inputFiles;
  int b;    /* buffer size */
  int numInputFiles;
} Args;

Args *getArgs(int argc, char *argv[]);
void printUsage(char *version);
void printSplash(char *version);

#endif
