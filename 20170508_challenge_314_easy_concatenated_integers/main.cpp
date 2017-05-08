#include <set>
#include <sstream>
#include <iostream>
#include <functional>
#include <conio.h>
#include <iterator>

const char * input[] =
{
   "79 82 34 83 69",
   "420 34 19 71 341",
   "17 32 91 7 46"
};

int main(int argc, char * argv[])
{
   const char ** in = input;
   while (*in)
   {
      std::stringstream ss;
      std::string item;
      ss << *in;
      auto nums = std::set<std::string, std::function<bool(const std::string & a, const std::string & b)>>{
         [](const std::string& a, const std::string& b)
         {
            if (b.find(a) != std::string::npos) return false;  // pick smaller lengthed strings over larger
            if (a.find(b) != std::string::npos) return true;
            return a < b;
         }
      };

      while (std::getline(ss, item, ' ')) { nums.insert(item); }

      std::copy(nums.begin(), nums.end(), std::ostream_iterator<std::string>(std::cout, ""));
      std::cout << " ";
      std::copy(nums.rbegin(), nums.rend(), std::ostream_iterator<std::string>(std::cout, ""));
      std::cout << std::endl;
      in++;
   }

   std::cout << std::endl << "Press any key to exit. "; _getch();
}

