/**
* @project: FilamentEditor
* @author: FilamentEditor Tech.
* @licence: MIT
*/

#include <iostream>
#include <sstream>

#include "FTools/Utils/Format.h"

std::string FTools::Utils::Format::ReadableNumber(const uint64_t number)
{
    std::stringstream ss;
    ss.imbue(std::locale(std::cout.getloc(), new DefaultNumberFormat));
    ss << number;

    return ss.str();
}