// Name: Francesco Menghi
// Date of completion: Nov 28, 2020
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include <utility>
#include <algorithm>
#include "LineManager.h"

LineManager::LineManager(const std::string &filename, std::vector<Workstation *> &stations, std::vector<CustomerOrder> &orders)
{
    std::ifstream file(filename);
    if (!file)
        throw std::string("Unable to open [") + filename + "] file.";

    std::string record;
    while (!file.eof())
    {
        Utilities util;
        size_t next_pos = 0;
        bool more = true;
        std::getline(file, record);
        std::string stationName = util.extractToken(record, next_pos, more);

        auto it = std::find_if(stations.begin(), stations.end(), [=](const Workstation *stn)
                               { return stn->getItemName() == stationName; });
        auto stationIdx = std::distance(stations.begin(), it);

        if (more)
        {
            std::string nextStationName = util.extractToken(record, next_pos, more);
            it = std::find_if(stations.begin(), stations.end(), [=](const Workstation *stn)
                              { return stn->getItemName() == nextStationName; });
            auto nextStationIdx = std::distance(stations.begin(), it);
            stations[stationIdx]->setNextStation(*stations[nextStationIdx]);
        }
    }
    file.close();

    std::move(begin(orders), end(orders), back_inserter(ToBeFilled));
    m_cntCustomerOrder = ToBeFilled.size();
    AssemblyLine = stations;

    initialIdx = getFirstStationIdx();
    cnt = 0;
}

size_t LineManager::getFirstStationIdx() const
{
    size_t idx = 0;
    for (size_t i = 0; i < AssemblyLine.size(); i++)
    {
        auto it = std::find_if(AssemblyLine.begin(), AssemblyLine.end(), [=](const Workstation *stn)
                               { return stn->getNextStation() == AssemblyLine[i]; });
        if (it == AssemblyLine.end())
            idx = i;
    }
    return idx;
}

bool LineManager::run(std::ostream &os)
{
    os << "Line Manager Iteration: " << ++cnt << std::endl;
    size_t idx = initialIdx;

    if (!ToBeFilled.empty())
    {
        // move the order at the front of the queue onto the starting point of the assembly line
        *AssemblyLine[idx] += std::move(ToBeFilled.front());
        ToBeFilled.pop_front();
    }

    for (auto &station : AssemblyLine)
        station->runProcess(os); // run one cycle of the station's process

    for (auto &station : AssemblyLine)
    {
        station->moveOrder(); // move the order down the line
        CustomerOrder complete;
        if (station->getIfCompleted(complete))
            Completed.push_back(std::move(complete));
    }

    return !(Completed.size() < m_cntCustomerOrder);
}

void LineManager::displayCompletedOrders(std::ostream &os) const
{
    for (const auto &order : Completed)
        order.display(std::cout);
}

void LineManager::displayStations() const
{
    for (const Workstation *station : AssemblyLine)
        station->display(std::cout);
}

void LineManager::displayStationsSorted() const
{
    size_t idx = initialIdx;
    for (size_t i = 0; i < AssemblyLine.size(); i++)
    {
        AssemblyLine[idx]->display(std::cout);
        bool found = false;
        for (size_t j = 0; j < AssemblyLine.size() && !found; j++)
        {
            if (AssemblyLine[j] == AssemblyLine[idx]->getNextStation())
            {
                idx = j;
                found = true;
            }
        }
    }
}
