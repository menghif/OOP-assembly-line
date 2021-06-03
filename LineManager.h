// Name: Francesco Menghi
// Date of completion: Nov 28, 2020
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#ifndef LINEMANAGER_H
#define LINEMANAGER_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include <utility>
#include <algorithm>
#include "Utilities.h"
#include "Workstation.h"
#include "CustomerOrder.h"

class LineManager
{
    std::vector<Workstation *> AssemblyLine;
    std::deque<CustomerOrder> ToBeFilled;
    std::deque<CustomerOrder> Completed;
    unsigned int m_cntCustomerOrder;
    size_t initialIdx;
    size_t cnt;

public:
    LineManager(const std::string &, std::vector<Workstation *> &, std::vector<CustomerOrder> &);
    size_t getFirstStationIdx() const;
    bool run(std::ostream &os);
    void displayCompletedOrders(std::ostream &os) const;
    void displayStations() const;
    void displayStationsSorted() const;
};

#endif