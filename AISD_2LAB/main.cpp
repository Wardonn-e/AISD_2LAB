#include <iostream>

using namespace std;

template<typename T>
struct Node {
    Node<T>* _next;
    T _data;
    Node(const T& data, Node<T>* next = nullptr) : _data(data), _next(next) {}
};

template<typename T>
class LinkedList {
private:
    Node<T>* _head;
public:
    LinkedList() : _head(nullptr) {}
};

int main() {
    LinkedList<int> a;
}
