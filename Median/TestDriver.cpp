#include "Median.hpp"
#include <assert.h>
#include <math.h>
#include <limits>
#include <algorithm>

bool Equal(double a, double b)
{
    return fabs(a - b) < std::numeric_limits<double>::epsilon();
}

int main()
{
    MedianFinder median;
    vector<int> validator;

    const int dataSize = 10000;
    double expectedMedian;
    double computedMedian;
    double lastMedian = 0;
    for (int i = 0; i < dataSize ; ++i)
    {
        int number = rand() % 1000;
        validator.push_back(number);
        sort(validator.begin(), validator.end());

        int mid = (validator.size() - 1) / 2;
        if (i % 2 == 0)
        {
            expectedMedian = validator[mid];
        }
        else
        {
        	expectedMedian = (validator[mid] + validator[mid + 1]) / 2.0;
        }

        median.Insert(number);
        computedMedian = median.GetMedian();

        if(Equal(computedMedian, expectedMedian) == false)
        {
            cout << "Test FAILED : Dumping the sorted stream " << endl;
            for(auto num : validator)
                cout << num << " ";
            cout << endl << "Arrived number = " << number << 
                ", Count = " << i + 1 << 
                " LastMedian = " << lastMedian << 
                " Expected median = " << expectedMedian << 
                ", Computed median " << computedMedian << endl;
            assert(false);
        }
        lastMedian = expectedMedian;
    }
    cout << "Test PASSED" << endl;
    return 0;

}


