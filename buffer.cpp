//
// Created by Mark Seeliger on 4/23/25.
//
using namespace std;
#include <vector>
#include <stdexcept>
template <typename T>
class CircularBuffer {
private:
    int head;
    int tail;
    bool full;
    int size;
    vector<T> vector;

    /* CONSTRUCTOR FOR CIRCULAR BUFFER
     *
     * */
    public: CircularBuffer(int capacity) {
        //head and tail both start at zero
        head = 0;
        tail = 0;

        //buffer is only bull if you give an invalid size
        full = size <= 0;
        size = capacity;
        vector = std::vector<T>(capacity);
    }

    /* This function adds an item to the buffer,
     * if the buffer is full, it removes the
     * oldest value
     * */
    public: void push(T val) {
        //set new value (may be overwriting something if vector is full)
        vector[head] = val;
        if(full) { //this also implies head == tail
            //if the vector was previously full we need to increment tail affectively activating the new value
            tail  = (tail + 1) % size;
        }

        //increment head for next push
        head = (head + 1) % size;

        //buffer is full if head and tail are the same (AND ITS NOT EMPTY) but since we just added something we know its not empty
        //so it must be full
        full = head == tail;

    }
    /* This function removes the oldest value from the buffer, returning a boolean indicating success/failure
     * */
    public: bool pop() {
        //if its empty theres nothing to remove
        if(isEmpty()) {
            return false;
        }

        //no longer full
        full = false;

        //increment tail pointer (goes back around with modulo)
        tail = (tail + 1) % size;
        return true;
    }
    /*its empty if head and tail are the same AND we didnt indicate full from are boolean*/
    public: bool isEmpty() {
        return !full && head == tail;
    }

    /*gets size*/
    public: int getSize() {
        //if the buffer is full the size if just the size of the buffer
        if(full) {
            return size;
            //otherwise if head is ahead of the tail we just have head - tail
        } else if(head >= tail) {
            return head - tail;
        } else if(tail > head){ //implicitly true here
            //otherwise we have size - (tail - head) which simplifies to size - tail + head
            return size + head - tail;
        }


    }

    /*If the buffer is not empty then we empty then we return the head otherwise throw an exception
     * */
    public: T getHead() {
        if(isEmpty()) {
            throw runtime_error("Empty Buffer");
        }
        if(head == 0) {
            return vector[size - 1];
        }
        return vector[head - 1];
    }

    /*
     * Returns tail if the buffer is not empty
     */
    T getTail() {
        if(isEmpty()) {
            throw runtime_error("Empty Buffer, No Tail");
        }
        return vector[tail];
    }






};