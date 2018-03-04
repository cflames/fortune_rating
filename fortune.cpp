
#include <sstream>
#include <istream>
#include <ostream>
#include <iterator>
#include <vector>
#include <map>
#include <algorithm>

#include <iostream>

#include "fortune.h"

namespace FortuneRating
{
void Fortune::init()
{
    // init wordcounter
    pWordCounter_ = std::make_unique<MapWordCounter>();
    pWordCounter_->init();
    std::cout << "Fortune has been initilized" << std::endl;
}

int Fortune::price(const std::string& adage)
{
    // remove punct
    std::string strNoPunct;
    std::remove_copy_if(adage.begin(), adage.end(),            
                        std::back_inserter(strNoPunct), //Store output           
                        std::ptr_fun<int, int>(&std::ispunct)  
                       );
    // to lower case
    std::transform(strNoPunct.begin(), strNoPunct.end(), strNoPunct.begin(), ::tolower);

    // tokenized the adage
    std::stringstream streamString(strNoPunct);

    // use stream iterators to copy the stream to the vector as whitespace separated strings
    std::istream_iterator<std::string> it(streamString);
    std::istream_iterator<std::string> end;
    std::vector<std::string> results(it, end);

    // use a map to count the word counter for this adage
    std::map<std::string, int> words;
    for ( auto it : results )
    {
        words[it]++;
    }

    float price = 0.0;
    for( auto word : words )
    {
        // get percenage based on all previous adage
        // should not update wordcounter because the percentage
        // is calcuated by all previous adage, not include this adage
        int count        = pWordCounter_ -> getCounter(word.first);
        int totalCount   = pWordCounter_ -> getTotalCounter();

        float wordPrice    = 0;
        float percentage = 0.0;  // percentage u
    
        if ( totalCount > 0 )
        {
            percentage = static_cast<float>(count) / static_cast<float>(totalCount);
        }

        // if u < 0.05, price is 2 SEK
        if ( percentage < 0.05 )
        {
            wordPrice = 2.0;
        }
        else // otherwise, use the u to calcuate price
        {
            // (100 - percentage*100) / 100
            wordPrice = 1.0 - percentage;
        }
        // total price is sum of each word
        price = price + wordPrice;
    }

    // update counters by event
    for( auto word : words )
    {
        pWordCounter_->updateCounter(word.first, word.second);
    }
    std::cout << "adage price: " << price << std::endl;
    return static_cast<int>(price);
}
}
