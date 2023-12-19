#include <iostream>
#include <cstdlib>

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
    
    
    LinkedList(size_t size, T min_value, T max_value) : _head(nullptr) {
        for (size_t i = 0; i < size; ++i) {
            T random_value = static_cast<T>(rand() % (max_value - min_value + 1) + min_value);
            push_head(random_value);
        }
    }
    ~LinkedList() {
        if (_head) {
            Node<T>* ptr = _head;
            do {
                Node<T>* temp = ptr;
                ptr = ptr->_next;
                delete temp;
            } while (ptr != _head);
        }
    }


    LinkedList(const LinkedList& a) : _head(nullptr) {
        Node<T>* ptr = a._head;
        do {
            push_tail(ptr->_data);
            ptr = ptr->_next;
        } while (ptr != a._head);
    }

    LinkedList& operator=(LinkedList a) {
        swap(a);
        return *this;
    }

    void swap(LinkedList& a) {
        std::swap(_head, a._head);
    }

    size_t size() {
        if (!_head) {
            return 0;
        }
        size_t size = 0;
        Node<T>* ptr = _head;
        do {
            ptr = ptr->_next;
            size++;
        } while (ptr != _head);
        return size;
    }

    void push_head(const T& data) {
        Node<T>* new_head = new Node<T>(data);
        if (!_head) {
            _head = new_head;
            _head->_next = _head;
            return;
        }
        Node<T>* temp = _head;
        while (temp->_next != _head) {
            temp = temp->_next;
        }
        temp->_next = new_head;
        new_head->_next = _head;
        _head = new_head;
    }

    ostream& print_link(ostream& os = cout) const {
        Node<T>* ptr = _head;
        if (!ptr) {
            os << "Список пуст" << endl;
            return os;
        }
        do {
            os << ptr->_data << ' ';
            ptr = ptr->_next;
        } while (ptr != _head);
        return os;
    }

    T& operator[](size_t index) {
        Node<T>* ptr = _head;
        for (size_t i = 0; i < index; i++) {
            ptr = ptr->_next;
            if (ptr == _head) {
                throw std::out_of_range("Index out of range");
            }
        }
        return ptr->_data;
    }

    Node<T>* get_head() const {
        return _head;
    }
};


int main() {
    LinkedList<int> a(1000000, 0, 1);
    a.print_link();
}
