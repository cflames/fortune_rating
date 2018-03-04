#ifndef FORTUNE_H_
#define FORTUNE_H_

#include "word_counter.h"

namespace FortuneRating
{
/******************************************************************************
* A class to calculate fortune for adage
******************************************************************************/   
class Fortune
{
public:
    explicit Fortune() {};

    /* Init resource used by Fortune */
    void init();

    /*
    calculate the price for a adage.
    1. Given all the previous adages, calculate the percentage of usage for every word. (u)
    2. The price for new words or rarely used < 5% are 2 SEK.
    3. Rest of the words will be calculated as it follows:  (100 - u) * 1 SEK / 100
    4. the price of adage is the sum of price of each word in this adage
    @param adage:  a adage to be tokenized and calcuate price
    @return the price for this whole adage
    */        
    int  price(const std::string& adage);

    ~Fortune() { pWordCounter_->stop(); };

private:
    std::unique_ptr<MapWordCounter> pWordCounter_; // smart pointer to wordcounter
};

}

#endif
