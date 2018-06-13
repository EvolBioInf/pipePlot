/***** pipePlot.c *********************************
 * Description: 
 * Author: Bernhard Haubold, haubold@evolbio.mpg.de
 * Date: Mon Aug  7 15:15:45 2017
 **************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "interface.h"
#include "eprintf.h"

void scanFile(FILE *fp, Args *args){
  ssize_t read;
  size_t len;
  char *line = NULL, *cmd;
  FILE *pipe;

  cmd = (char *)emalloc(1024);
  cmd[0] = '\0';
  cmd = strcat(cmd, "gnuplot -p -e '");
  if(args->x){
    cmd = strcat(cmd, "set xlabel \"");
    cmd = strcat(cmd, args->x);
    cmd = strcat(cmd, "\"; ");
  }
  if(args->y){
    cmd = strcat(cmd, "set ylabel \"");
    cmd = strcat(cmd, args->y);
    cmd = strcat(cmd, "\"; ");
  }
  if(args->p){
    cmd = strcat(cmd, "set terminal postscript portrait; ");
    if(!args->s)
      cmd = strcat(cmd, "set size 0.8,0.5; ");
  }else if(args->D){
    cmd = strcat(cmd, "set terminal dumb; ");
  }
  if(args->s){
    cmd = strcat(cmd, "set size ");
    cmd = strcat(cmd, args->s);
    cmd = strcat(cmd, "; ");
  }
  if(args->l){
    cmd = strcat(cmd, "set logscale ");
    if(args->l == 1)
      cmd = strcat(cmd, "x; ");
    else if(args->l == 2)
      cmd = strcat(cmd, "y; ");
    else
      cmd = strcat(cmd, "xy; ");
  }
  cmd = strcat(cmd, "plot[");
  if(args->X)
    cmd = strcat(cmd, args->X);
  cmd = strcat(cmd, "][");
  if(args->Y)
    cmd = strcat(cmd, args->Y);
  cmd = strcat(cmd, "] \"< cat\" ");
  cmd = strcat(cmd, "title \"");
  if(args->t)
    cmd = strcat(cmd, args->t);
  cmd = strcat(cmd, "\" ");
  if(args->P)
    cmd = strcat(cmd, "with linespoints; ");
  else if(!args->d)
    cmd = strcat(cmd, "with lines; ");
  cmd = strcat(cmd, "'\n");
  if(args->c){
    printf("%s", cmd);
    exit(0);
  }
  pipe = popen(cmd, "w");
  while((read = getline(&line, &len, fp)) != -1)
    fprintf(pipe, "%s", line);
}

int main(int argc, char *argv[]){
  int i;
  char *version;
  Args *args;
  FILE *fp;

  version = "0.4";
  setprogname2("pipePlot");
  args = getArgs(argc, argv);
  if(args->v)
    printSplash(version);
  if(args->h || args->e)
    printUsage(version);
  if(args->numInputFiles == 0){
    fp = stdin;
    scanFile(fp, args);
  }else{
    for(i=0;i<args->numInputFiles;i++){
      fp = efopen(args->inputFiles[i],"r");
      scanFile(fp, args);
      fclose(fp);
    }
  }
  free(args);
  free(progname());
  return 0;
}

