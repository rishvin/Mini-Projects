#include "Median.hpp"

using namespace std;

MedianFinder::MedianFinder()
    :storeMngr(10), storeNode(-1, -0, -1), total(0), median(0)
{
}

void MedianFinder::Insert(int number)
{
    storeMngr.Insert(number);
    ++total;
    if (total == 1)
    {
        storeNode = storeMngr.GetFirst();
        median = storeNode.GetData();
    }
    else if (number >= storeNode.GetData())
    {
        if (total % 2 != 0)
        {
            storeNode = storeMngr.GetNext(storeNode);
            median = storeNode.GetData();
        }
        else
        {
            StoreNode node = storeMngr.GetNext(storeNode);
            median = (storeNode.GetData() + node.GetData()) / 2.0;
        }
    }
    else
    {
        if (total % 2 != 0)
        {
            median = storeNode.GetData();
        }
        else
        {
            int prevMedian = storeNode.GetData();
            storeNode = storeMngr.GetPrev(storeNode);
            median = (storeNode.GetData() + prevMedian) / 2.0;
        }
    }
}

double MedianFinder::GetMedian()
{
    return median;
}

