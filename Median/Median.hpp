#pragma once

#include "Store.hpp"

class MedianFinder
{
public :
    MedianFinder();
    void Insert(int number);
    double GetMedian();
private:
    StoreMngr storeMngr;
    StoreNode storeNode;
    int total;
    double median;
};
