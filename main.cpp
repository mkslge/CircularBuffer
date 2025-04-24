#include <iostream>
#include "buffer.cpp"
using namespace std;

int main() {
    CircularBuffer<int> buffer(3);
    buffer.push(1);
    buffer.push(2);
    buffer.push(3);
    buffer.push(900);


    return 0;
}
