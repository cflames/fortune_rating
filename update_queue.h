#include <pthread.h>
#include <list>

namespace FortuneRating
{
/******************************************************************************
* A class for threadsafe queue
******************************************************************************/   
template <typename T> class UpdateQueue
{
public:
    UpdateQueue() 
    {
        pthread_mutex_init(&mutex_, NULL);
        pthread_cond_init(&condv_, NULL);
    }

    ~UpdateQueue() 
    {
        pthread_mutex_destroy(&mutex_);
        pthread_cond_destroy(&condv_);
    }

    /*
    add an item into queue.
    @param item:  the new item in queue
    */    
    void add(T item) 
    {
        pthread_mutex_lock(&mutex_);
        queue_.push_back(item);
        pthread_cond_signal(&condv_);
        pthread_mutex_unlock(&mutex_);
    }

    /*
    remove an item from queue.
    @return the first item in the queue
    */    
    T remove() 
    {
        pthread_mutex_lock(&mutex_);
        while ( queue_.size() == 0 ) 
        {
            pthread_cond_wait(&condv_, &mutex_);
        }
        T item = queue_.front();
        queue_.pop_front();
        pthread_mutex_unlock(&mutex_);
        return item;
    }

    /*
    get queue size.
    @return the size of queue
    */       
    int size() 
    {
        pthread_mutex_lock(&mutex_);
        int size = queue_.size();
        pthread_mutex_unlock(&mutex_);
        return size;
    }

private:
    std::list<T>    queue_;
    pthread_mutex_t mutex_;
    pthread_cond_t  condv_;
    
};
}