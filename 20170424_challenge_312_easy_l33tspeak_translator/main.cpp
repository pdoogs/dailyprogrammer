#include <cctype>
#include <string>

std::string ToLeet(char c)
{
   c = toupper(c);
   if (c == 'A') return "4";
   if (c == 'B') return "6";
   if (c == 'E') return "3";
   if (c == 'I' || c == 'L') return "1";
   if (c == 'M') return "(V)";
   if (c == 'N') return "(\\)";
   if (c == 'O') return "0";
   if (c == 'S') return "5";
   if (c == 'T') return "7";
   if (c == 'V') return "\\/";
   if (c == 'W') return "`//";
}

int main()
{
   char inbuf[] = "I am elite. Da pain!\nEye need help!\n3Y3(\)33d j00 t0 g37 d4 d0c70r.\n1 n33d m4 p1llz!";
   printf("Input:\n%s\n", inbuf);
   char outbuf[256] = {};
   bool translated = false;

   int inlen = strlen(inbuf);
   int unconvertedCount = 0;
   char * in = inbuf;
   char * out = outbuf;
   do
   {
      char c = *in;
      switch (c)
      {
         case 'A': *out++ = '4'; break;
         case 'B': *out++ = '6'; break;
         case 'E': *out++ = '3'; break;
         case 'I': *out++ = '1'; break;
         case 'L': *out++ = '1'; break;
         case 'M': *out++ = '('; *out++ = 'V'; *out++ = ')'; break;
         case 'N': *out++ = '('; *out++ = '\\'; *out++ = ')'; break;
         case 'O': *out++ = '0'; break;
         case 'S': *out++ = '5'; break;
         case 'T': *out++ = '7'; break;
         case 'V': *out++ = '\/'; break;
         case 'W': *out++ = '`'; *out++ = '/'; *out++ = '/'; break;
         case '4': *out++ = 'A'; break;
         case '6': *out++ = 'B'; break;
         case '3': *out++ = 'E'; break;
         case '1': *out++ = 'I'; break; // could also output L
         case '(':
         {
            if ((in[1] == 'V') && (in[2] == ')'))
            {
               *out++ = 'M';
               in += 2;
            }
            else if ((in[1] == '\\') && (in[2] == ')'))
            {
               *out++ = 'N';
               in += 2;
            }
            else
            {
               *out++ = '(';
            }
         }
         break;
         case '0': *out++ = 'O'; break;
         case '5': *out++ = 'S'; break;
         case '7': *out++ = 'T'; break;
         case '\\':
         {
            if (in[1] == '/')
            {
               *out++ = 'V';
               in++;
            }
            else
            {
               *out++ = '\\';
            }
            break;
         }
         case '`':
            if ((in[1] == '/') && (in[2] == '/'))
            {
               *out++ = 'W';
               in += 2;
            }
            else
            {
               *out++ = '`';
            }
            break;
         default:
            *out++ = c;
            break;
      }

   } while (*in++ != 0);

   printf("\nOutput:%s\n", outbuf);
}