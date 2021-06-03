// Name: Francesco Menghi
// Date of completion: Nov 28, 2020
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#ifndef WORKSTATION_H
#define WORKSTATION_H

#include <queue>
#include "Station.h"
#include "CustomerOrder.h"

class Workstation : public Station
{
    std::deque<CustomerOrder> m_orders;
    Station *m_pNextStation;

public:
    Workstation(const std::string &line);
    Workstation(const Workstation &other) = delete;
    Workstation &operator=(const Workstation &other) = delete;
    Workstation(Workstation &&other) = delete;
    Workstation &operator=(Workstation &&other) = delete;
    void runProcess(std::ostream &);
    bool moveOrder();
    void setNextStation(Station &station);
    const Workstation *getNextStation() const;
    bool getIfCompleted(CustomerOrder &order);
    void display(std::ostream &os) const;
    Workstation &operator+=(CustomerOrder &&);
};

#endif