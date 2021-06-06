#pragma once
#include <string>
#include "../C/GPTypes.h"

class GPUtils
{
   public:
      static std::string hex2binaryString(const char* src);   // Convert a sequence of string hex characters into a sequence of bytes
      static std::string hex2binaryString(const std::string & src);

      static double Scale(double x, double xMin, double xMax, double yMin, double yMax);

      static std::string intToHex(uint8_t intValue); // Convert a byte into a string hex representation

      static bool fileExists(std::string filename);
      static void loadTextFile(std::string filename, std::string & text); // Load a text file into a string
};
