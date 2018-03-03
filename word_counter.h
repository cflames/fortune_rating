#ifndef WORD_BANK_H_
#define WORD_BANK_H_

#include <string>
#include <atomic>
#include <map>
#include <tuple>
#include<thread>
#include "update_queue.h"

namespace FortuneRating
{

class UpdateCounterEvent
{
public:
    explicit UpdateCounterEvent(int counter, std::string word):
        counter_(counter), word_(word) {};
    int getCounter() const { return counter_; };
    std::string getWord() const { return word_; };

private:
    int counter_;
    std::string word_;
};

/******************************************************************************
 * A class to save words with map
******************************************************************************/   
typedef std::atomic<uint64_t> value_t;
typedef std::map<std::string, value_t> atomic_map_t;

class MapWordCounter
{
public:
    explicit MapWordCounter(): total_word_count_(0) {};

    /*
    get counter for a word.

    @param word: the target word for getting counter.
    @return the counter for this word
    */
    int getCounter(const std::string& word) const;

    /*
    get total counter for all words.
    @return the total counter for this word
    */
    int getTotalCounter() const { return total_word_count_; };

    /*
    update counter for a word with the count.

    @param word:  the target word for updating price
    @param count: the number of this word to be put into word bank
    */     
    void updateCounter(const std::string& word, int count);

    // init word counter, run start with main event loop
    void init();
    // stop main loop thread
    void stop();
private:
    // main loop for this word counter to handle update event
    void event_loop(MapWordCounter* object);

private:
    value_t total_word_count_; // the number of words in this data store in total
    atomic_map_t words_; // the map to save words and counter
    UpdateQueue<UpdateCounterEvent*> eventQueue_; // the update event queue
    bool isRunning_; // flag to stop thread
    std::thread thread_;
};

}

#endif /* WORD_BANK_H_ */