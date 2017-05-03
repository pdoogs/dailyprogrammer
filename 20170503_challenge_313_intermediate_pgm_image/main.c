#include <stdio.h>
#include <stdlib.h>

#define swapint(a, b) { int tmp = a; a = b; b = tmp; }
#define swapptr(a, b) { int * tmp = a; a = b; b = tmp; }

void transpose(int * in, int width, int height, int * out)
{
   for (int j = 0; j < height; j++)
      for (int i = 0; i < width; i++)
         out[i*height + j] = in[j*width + i];
}

void reflectVert(int * in, int width, int height, int * out)
{
   for (int j = 0; j < height; j++)
      for (int i = 0; i < width; i++)
         out[j*width + i] = in[(height-j-1)*width + i];
}

int main(int argc, char * argv[])
{
   if (argc != 4) { fprintf(stderr, "Usage: [string of HVLR commands] [input file path] [output file path]\n"); }
   const char * cmd = argv[1];
   FILE * fpin, *fpout;
   fopen_s(&fpin, argv[2], "r");
   fopen_s(&fpout, argv[3], "w");
   char buf[3] = "";
   fread(buf, sizeof(buf), 1, fpin);
   if (buf[0] != 'P' || buf[1] != '2')
   { 
      fprintf(stderr, "Bad input file %s", argv[2]); exit(1); 
   }
   int width, height, maxVal;
   fscanf_s(fpin, "%d %d %d", &width, &height, &maxVal);
   int * vals = malloc(width * height * sizeof(int));
   int * tmp = malloc(width * height * sizeof(int));
   int * curVal = vals;
   while (fscanf_s(fpin, "%d", curVal++) == 1);
   fclose(fpin);

   memcpy(tmp, vals, width * height * sizeof(int));
   int * curr = vals, *next = tmp;;
   while (cmd && *cmd) 
   {
      if (*cmd == 'L') 
      {
         transpose(curr, width, height, next); 
         reflectVert(next, height, width, curr); 
         swapint(width, height);
      }
      else if (*cmd == 'R') 
      { 
         reflectVert(curr, width, height, next); 
         transpose(next, width, height, curr); 
         swapptr(curr, next); 
         swapint(width, height);
      }
      else if (*cmd == 'V') 
      { 
         reflectVert(curr, width, height, next); 
         swapptr(curr, next); 
      }
      else if (*cmd == 'H') 
      { 
         transpose(curr, width, height, next); 
         reflectVert(next, height, width, curr); 
         transpose(curr, height, width, next); 
         swapptr(curr, next); 
      }
      cmd++;
   }
   fprintf(fpout, "P2 %d %d %d\n", width, height, maxVal);
   for (int i = 0; i < width * height; i++) fprintf(fpout, "%d\n", curr[i]);
   fclose(fpout);
   free(tmp);
   free(vals);
   return 0;
}