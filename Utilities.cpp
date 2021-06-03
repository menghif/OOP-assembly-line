// Name: Francesco Menghi
// Date of completion: Nov 28, 2020
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include <string>
#include "Utilities.h"

char Utilities::m_delimiter = 0;

void Utilities::setFieldWidth(size_t newWidth)
{
    m_widthField = newWidth;
}

size_t Utilities::getFieldWidth() const
{
    return m_widthField;
}

std::string Utilities::extractToken(const std::string &str, size_t &next_pos, bool &more)
{
    std::string tmpStr = str;
    std::string token;
    size_t n = tmpStr.find(m_delimiter, next_pos);

    if (tmpStr.find(m_delimiter, next_pos) != std::string::npos)
    {
        // if no data between 2 delimiters
        if (tmpStr[n] == tmpStr[n + 1])
            throw "No data";

        token = tmpStr.substr(next_pos, n - next_pos);

        if (m_widthField < n - next_pos)
            m_widthField = n - next_pos;
        next_pos = n;
        next_pos++;
        more = true;
    }
    else
    {
        token = tmpStr.substr(next_pos);
        more = false;
    }

    return token;
}

void Utilities::setDelimiter(char newDelimiter)
{
    m_delimiter = newDelimiter;
}

char Utilities::getDelimiter()
{
    return m_delimiter;
}
