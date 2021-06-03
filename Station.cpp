// Name: Francesco Menghi
// Date of completion: Nov 28, 2020
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include <iostream>
#include <string>
#include <iomanip>
#include <algorithm>
#include "Station.h"

size_t Station::m_widthField = 0;
int Station::id_generator = 0;

Station::Station(const std::string &line)
{
    id = ++id_generator;
    Utilities util;
    size_t next_pos = 0;
    bool more = true;

    m_itemName = util.extractToken(line, next_pos, more);

    std::string tmp = util.extractToken(line, next_pos, more);
    m_serialNumber = std::stoi(tmp);

    tmp = util.extractToken(line, next_pos, more);
    m_stockQuantity = std::stoi(tmp);

    if (m_widthField < util.getFieldWidth())
        m_widthField = util.getFieldWidth();

    m_itemDesc = util.extractToken(line, next_pos, more);
}

const std::string &Station::getItemName() const
{
    return m_itemName;
}

unsigned int Station::getNextSerialNumber()
{
    return m_serialNumber++;
}

unsigned int Station::getQuantity() const
{
    return m_stockQuantity;
}

void Station::updateQuantity()
{
    if (m_stockQuantity > 0)
        m_stockQuantity--;
}

void Station::display(std::ostream &os, bool full) const
{
    os << "[";
    os.fill('0');
    os.width(3);
    os << id << "] Item: ";
    os.fill(' ');
    os.width(m_widthField);
    os.setf(std::ios::left);
    os << m_itemName << " [";
    os.unsetf(std::ios::left);
    os.width(6);
    os.fill('0');
    os << m_serialNumber << "]";

    if (full)
    {
        os << " Quantity: ";
        os.setf(std::ios::left);
        os.width(m_widthField);
        os.fill(' ');
        os << m_stockQuantity;
        os << " Description: " << m_itemDesc;
        os.unsetf(std::ios::left);
    }
    os << std::endl;
}
