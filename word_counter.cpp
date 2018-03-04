
#include "word_counter.h"

#include <iostream>

namespace FortuneRating
{

int MapWordCounter::getCounter(const std::string& word) const
{
    const auto it = words_.find(word);
    if ( it != words_.end() )
    {
        return it->second;
    }
    // if word is not presented before, return 0
    return 0;
}

void MapWordCounter::updateCounter(const std::string& word, int count)
{
    eventQueue_.add(std::make_shared<UpdateCounterEvent>(UpdateCounterEvent(count, word)));
}

void MapWordCounter::event_loop(MapWordCounter* object)
{
    while ( isRunning_ ) {
        if ( eventQueue_.size() == 0 )
        {
            continue;
        }
        std::shared_ptr<UpdateCounterEvent> event = eventQueue_.remove();
        //std::cout << "get a new event " << event->getCounter() << std::endl;
        total_word_count_ = total_word_count_ + event->getCounter();

        auto it = words_.find(event->getWord());

        // if it's a new word
        if ( it == words_.end() )
        {
            words_.emplace(std::piecewise_construct,
                std::forward_as_tuple(event->getWord()), std::forward_as_tuple(event->getCounter()));
            continue;
        }
        //std::cout << "this is old word" << event->getWord() << std::endl;
        // set new counter
        it->second = it->second + event->getCounter();
    }
    
}

void MapWordCounter::stop()
{
    isRunning_ = false;
    thread_.join();
}

void MapWordCounter::init()
{
    isRunning_ = true;
    thread_ = std::thread(&MapWordCounter::event_loop, this, this);
}

}