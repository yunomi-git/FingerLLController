#ifndef __ALPHAFILTER__
#define __ALPHAFILTER__

template <typename T> class AlphaFilter
{
    T lastData;
    float alpha;

public:
    AlphaFilter(float alpha=1.0)
    {
        this->alpha = alpha;
    }

    void update(T data)
    {
        lastData = (alpha * data + (1.0 - alpha) * lastData);
    }

    T getFilteredData()
    {
        return lastData;
    }

    void setAlpha(float alpha)
    {
        this->alpha = alpha;
    }


};

#endif