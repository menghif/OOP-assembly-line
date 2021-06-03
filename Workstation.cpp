// Name: Francesco Menghi
// Date of completion: Nov 28, 2020
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include <queue>
#include "Workstation.h"

Workstation::Workstation(const std::string &line) : Station(line)
{
    m_pNextStation = nullptr;
}

void Workstation::runProcess(std::ostream &os)
{
    if (!m_orders.empty())
        m_orders.front().fillItem(*this, os);
}

bool Workstation::moveOrder()
{
    bool done = false;
    if (!m_orders.empty() && m_pNextStation && m_orders.front().isItemFilled(getItemName()))
    {
        *dynamic_cast<Workstation *>(m_pNextStation) += std::move(m_orders.front());
        m_orders.pop_front();
        done = true;
    }
    return done;
}

void Workstation::setNextStation(Station &station)
{
    m_pNextStation = &station;
}

const Workstation *Workstation::getNextStation() const
{
    return dynamic_cast<Workstation *>(m_pNextStation);
}

bool Workstation::getIfCompleted(CustomerOrder &order)
{
    bool get = false;
    if (!m_orders.empty() && m_orders.front().isOrderFilled())
    {
        order = std::move(m_orders.front());
        m_orders.pop_front();
        get = true;
    }
    return get;
}

void Workstation::display(std::ostream &os) const
{
    if (m_pNextStation)
        os << getItemName() << " --> " << m_pNextStation->getItemName() << std::endl;
    else
        os << getItemName() << " --> END OF LINE" << std::endl;
}

Workstation &Workstation::operator+=(CustomerOrder &&order)
{
    m_orders.push_back(std::move(order));
    return *this;
}
