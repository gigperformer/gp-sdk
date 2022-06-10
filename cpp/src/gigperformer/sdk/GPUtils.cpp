#include "gigperformer/sdk/GPUtils.h"

#include <assert.h>

#include <algorithm>
#include <fstream>
#include <iomanip>
#include <sstream>

#include "gigperformer/sdk/utils.h"
#define then

namespace gigperformer
{
namespace sdk
{

bool GPUtils::fileExists(std::string filename)
{
    // bool exists = access( filename.c_str(), F_OK ) != -1;
    // return exists;
    std::ifstream myfile(filename);
    bool exists = myfile.good();

    return exists;
}

void GPUtils::loadTextFile(std::string filename, std::string &text)
{
    if (fileExists(filename))
        then
        {
            std::ifstream t(filename);
            std::stringstream buffer;
            buffer << t.rdbuf();
            text = buffer.str();
        }
    else
        text.clear();
}

double GPUtils::Scale(double x, double xMin, double xMax, double yMin, double yMax)
{
    double y = yMin + ((yMax - yMin) * (x - xMin)) / (xMax - xMin);
    return y;
}

std::string GPUtils::hex2binaryString(const std::string &src)
{
    std::string source{src}; // We're going to eliminate all spaces
    source.erase(remove(source.begin(), source.end(), ' '), source.end());
    int sourceLength = (int)source.size();
    int targetLength = sourceLength / 2;

    std::string target;
    target.resize(targetLength);
    hex2bin(source.c_str(), (uint8_t *)target.c_str());

    return target;
}

std::string GPUtils::hex2binaryString(const char *src)
{
    std::string source{src};

    std::string result = hex2binaryString(source);
    return result;
}

std::string GPUtils::intToHex(uint8_t intValue)
{
    std::stringstream sstream;
    sstream << std::setfill('0') << std::setw(2) << std::hex << (int)(intValue & 0x7f);

    std::string hexStr = sstream.str();
    // sstream.clear();    //clears out the stream-string

    return hexStr;
}

} // namespace sdk
} // namespace gigperformer
