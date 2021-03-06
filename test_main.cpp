
#include "fortune.h"

#include "word_counter.h"

#include <chrono>
#include <thread>
#include <iostream>
#include <string>
#include <cassert>
#include <sstream> 


void test_word_counter()
{
    FortuneRating::MapWordCounter wordcounter;
    wordcounter.init();

    wordcounter.updateCounter("test", 1);
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    int count = wordcounter.getCounter("test");
    assert(count == 1);

    wordcounter.updateCounter("test1", 5);
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    count = wordcounter.getCounter("test1");
    assert(count == 5);

    wordcounter.updateCounter("test", 3);
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    count = wordcounter.getCounter("test");
    assert(count == 4);

    count = wordcounter.getTotalCounter();
    assert(count == 9);

    wordcounter.stop();
}

void test_fortune()
{
    FortuneRating::Fortune fortune;
    fortune.init();

    std::string test("test test1 test2 test");
    int price = fortune.price(test);
    assert( price == 6 ); // because no previous adage, percentage always 0

    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    price = fortune.price(test);
    // test percentage is 50%, others are 25%
    // (100 - 50) /100 + (100 - 25)/100 + (100 - 25)/100
    assert( price == 2);

    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    std::string test2("Test, tesT1! test2. test ");
    // test percentage is 50%, others are 25%
    price = fortune.price(test);
    assert( price == 2);

    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    std::ostringstream stringStream;
    for ( int i=0; i < 100; i++)
    {
        stringStream << "test" << i << " ";
    }
    std::string copyOfStr = stringStream.str();
    price = fortune.price(copyOfStr);
    // 98*2 SEK + 0.75 + 0.75
    assert( price == 197);

    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    std::string test3("test100");
    price = fortune.price(test3);
    assert( price == 2);

    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    std::string test4("test10");
    price = fortune.price(test4);
    assert( price == 2);
}

int main(int argc, const char *argv[])
{
   test_word_counter();
   std::cout << "Test test_word_counter is passed" << std::endl;

   test_fortune();
   std::cout << "Test test_fortune is passed" << std::endl;
}