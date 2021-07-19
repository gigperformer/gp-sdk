/// \file    GPUtils.h
/// \brief   Helpful functions for C++ extension implementers

#pragma once

#include <string>

#include "gigperformer/sdk/types.h"

namespace gigperformer
{
namespace sdk
{

class GPUtils
{
  public:
    /// \brief   Convert a sequence of string hex characters into a sequence of bytes
    static std::string hex2binaryString(const char *src);

    /// \brief   Convert a sequence of string hex characters into a sequence of bytes
    static std::string hex2binaryString(const std::string &src);

    /// \brief   Scale the input value x in [xMin, xMax] linearly to the range given [yMin, yMax]
    /// \param   x input value to scale
    /// \param   xMin lower bound of the input range
    /// \param   xMax upper bound of the input range
    /// \param   yMin lower bound of the output range
    /// \param   yMax upper bound of the output range
    static double Scale(double x, double xMin, double xMax, double yMin, double yMax);

    /// \brief   Convert a byte into a string hex representation.
    static std::string intToHex(uint8_t intValue);

    /// \brief   Returns true if a file with the given name exists.
    static bool fileExists(std::string filename);

    /// \brief   Load the contents of a textfile into the string text.
    static void loadTextFile(std::string filename, std::string &text);
};

} // namespace sdk
} // namespace gigperformer
