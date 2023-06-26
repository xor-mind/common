#include "FileUtilities.h"

bool IsFileEmpty(std::ifstream& pFile)
{
    return pFile.peek() == std::ifstream::traits_type::eof();
}