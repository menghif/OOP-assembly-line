// Name: Francesco Menghi
// Date of completion: Nov 28, 2020
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#ifndef STATION_H
#define STATION_H

#include <iostream>
#include <string>
#include <iomanip>
#include <algorithm>
#include "Utilities.h"

class Station
{
    int id = 0;
    std::string m_itemName;
    std::string m_itemDesc;
    int m_serialNumber;
    int m_stockQuantity;
    static size_t m_widthField;
    static int id_generator;

public:
    Station(const std::string &line);
    const std::string &getItemName() const;
    unsigned int getNextSerialNumber();
    unsigned int getQuantity() const;
    void updateQuantity();
    virtual void display(std::ostream &os, bool full) const;
};

#endif