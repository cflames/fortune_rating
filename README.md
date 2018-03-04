# fortune_rating

1. environment <br/>
Ubuntu 16.04,  gcc version 5.4.0 <br/>

2. how to run test<br/>
   make test<br/>

3. File structure<br/>
    
    fortune: implement the price and init function for adage, it tokenized the adage<br/>
             then calculate price for each price, return the sum of each word price.<br/>
             the count of each word is saved in WordCounter class, as well as the total<br/>
             counter. To be able to return price immediately, the word counter is updated <br/>
             with async event<br/>
    <br/>
    word_counter: implement a event-based async word counter, it save word and counter in <br/>
            a map, when updateCounter is called, a event is generated and push into a queue<br/>
            In WordCounter init function, it starts a Thread which monitor the queue and<br/>
            handle event if there is a new event<br/>
    <br/>        
    test_main.cpp: unit test for other classes<br/>
    '''
