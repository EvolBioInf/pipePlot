/***** interface.c ************************************************
 * Description: Routine for gathering arguments from the command
 *              line.
 * Author: Bernhard Haubold, haubold@evolbio.mpg.de
 * Date: Sun Jun 20 13:12:10 2004.
 *****************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "interface.h"
#include "eprintf.h"

Args *args;

Args *getArgs(int argc, char *argv[]){
  char c;
  char *optString = "hvpPdDdcl:s:X:Y:x:y:t:";

  args = (Args *)emalloc(sizeof(Args));
  args->x = NULL;
  args->y = NULL;
  args->X = NULL;
  args->Y = NULL;
  args->t = NULL;
  args->s = NULL;
  args->c = 0;
  args->l = 0;
  args->d = 0;
  args->D = 0;
  args->P = 0;
  args->p = 0;
  args->h = 0;
  args->v = 0;
  args->e = 0;

  c = getopt(argc, argv, optString);
  while(c != -1){
    switch(c){
    case 'x':                           /* x-label */
      args->x = estrdup(optarg);
      break;
    case 'y':                           /* y-label */
      args->y = estrdup(optarg);
      break;
    case 't':                           /* title */
      args->t = estrdup(optarg);
      break;
    case 's':                           /* size  */
      args->s = estrdup(optarg);
      break;
    case 'l':                           /* log scale */
      args->l = atoi(optarg);
      break;
    case 'c':                           /* print command */
      args->c = 1;
      break;
    case 'p':                           /* postscript? */
      args->p = 1;
      break;
    case 'D':                           /* dumb terminal? */
      args->D = 1;
      break;
    case 'd':                           /* with dots? */
      args->d = 1;
      break;
    case 'P':                           /* linespoints? */
      args->P = 1;
      break;
    case 'X':                           /* x-range */
      args->X = estrdup(optarg);
      break;
    case 'Y':                           /* y-range */
      args->Y = estrdup(optarg);
      break;
    case '?':                           /* fall-through is intentional */
    case 'h':                           /* print help */
      args->h = 1;
      break;
    case 'v':                           /* print version */
      args->v = 1;
      break;
    default:
      printf("# unknown argument: %c\n",c);
      args->e = 1;
      return args;
    }
    c = getopt(argc, argv, optString);
  }
  args->inputFiles = argv + optind;
  args->numInputFiles = argc - optind;
  return args;
}


void printUsage(char *version){
  printf("Usage: %s [options] [inputFiles]\n",progname());
  printf("Wrap gnuplot for piping\n");
  printf("Example: cat test.dat | pipePlot\n");
  printf("Options:\n");
  printf("\t[-x <STRING> x-label]\n");
  printf("\t[-y <STRING> y-label]\n");
  printf("\t[-s x,y size]\n");
  printf("\t[-X s:e x-range]\n");
  printf("\t[-Y s:e y-range]\n");
  printf("\t[-l 1|2|3 logscale x (1), y (2), or xy (3)]\n");
  printf("\t[-p postscript output]\n");
  printf("\t[-D dumb terminal]\n");
  printf("\t[-d with dots; default: lines]\n");
  printf("\t[-c print command and exit]\n");
  printf("\t[-P with linespoints; default: just lines]\n");
  printf("\t[-h print this help message and exit]\n");
  printf("\t[-v print program information and exit]\n");
  exit(0);
}

void printSplash(char *version){
  printf("%s %s\n",progname(),version);
  printf("Written by Bernhard Haubold.\n");
  printf("Distributed under the GNU General Public License.\n");
  printf("Please send bug reports to haubold@evolbio.mpg.de\n");
  exit(0);
}
