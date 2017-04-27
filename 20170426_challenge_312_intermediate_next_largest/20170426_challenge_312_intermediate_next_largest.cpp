// 20170426_challenge_312_intermediate_next_largest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <map>
#include <stdlib.h>
#include <string.h>

using namespace std;

const char * input[] = {
   "1234",
   "1243",
   "234765",
   "234744",
   "19000",
   nullptr
};

void Process(const char * in)
{
   int len = strlen(in);
   char out[256] = {};
   int i=0, k;
   map<char, int> charmap;

   while (in[i] < in[i + 1] && i + 1 < len) i++;
   if (i > 0) i--;
   for (int j = i + 1; j < len; j++) charmap[in[j]]++;
   for (k = 0; k < i; k++) out[k] = in[k];

   auto it = charmap.begin();
   while (it != charmap.end() && it->first == '0') it++;
   out[k++] = it->first;
   it->second--;
   if (it->second <= 0) charmap.erase(it->first);
   charmap.insert(make_pair(in[i], 1));

   while (!charmap.empty()) 
   { 
      auto it = charmap.begin();
      out[k++] = it->first;
      it->second--;
      if (it->second <= 0) charmap.erase(it->first);
   }
   printf("%s\n", out);
}

int main()
{
   const char ** in = input;
   while (*in)
   {
      Process(*in);
      in++;
   }
}

