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
            push_tail(random_value);
        }
    }
    ~LinkedList() {
        if (_head) {
            Node<T>* ptr = _head;
            do {
                Node<T>* temp = ptr;
                ptr = ptr->_next;
                delete temp;
            } while (ptr && ptr != _head);

            _head = nullptr;
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
        while (temp->_next != _head)
        {
            temp = temp->_next;
        }
        temp->_next = new_head;
        new_head->_next = _head;
        _head = new_head;
    }
    void push_tail(const T& data) {
        Node<T>* new_head = new Node<T>(data);
        if (!_head) {
            _head = new_head;
            _head->_next = _head;
            return;
        }
        Node<T>* temp = _head;
        while (temp->_next != _head)
        {
            temp = temp->_next;
        }
        temp->_next = new_head;
        new_head->_next = _head;
    }
    void push_head(LinkedList a) {
        a.push_tail(*this);
        swap(a);
    }

    void push_tail(const LinkedList& a) {
        Node<T>* ptr = a._head;
        do {
            push_tail(ptr->_data);
            ptr = ptr->_next;
        } while (ptr != a._head);
    }

    ostream& print(ostream& os = cout) const {
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

    const T& operator[](size_t index) const {
        Node<T>* ptr = _head;
        for (size_t i = 0; i < index; i++) {
            ptr = ptr->_next;
            if (ptr == _head) {
                throw std::out_of_range("Index out of range");
            }
        }
        return ptr->_data;
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

    void pop_head() {
        if (!_head) {
            throw out_of_range("List empty");
        }
        if (_head->_next == _head) {
            delete _head;
            _head = nullptr;
            return;
        }
        Node<T>* ptr = _head;
        while (ptr->_next != _head) {
            ptr = ptr->_next;
        }
        Node<T>* temp = _head;
        ptr->_next = _head->_next;
        _head = _head->_next;
        delete temp;
    }

    void pop_tail() {
        if (!_head) {
            throw out_of_range("List empty");
        }
        if (_head->_next == _head) {
            delete _head;
            _head = nullptr;
            return;
        }
        Node<T>* ptr = _head;
        while (ptr->_next->_next != _head) {
            ptr = ptr->_next;
        }
        Node<T>* tail = ptr->_next;
        ptr->_next = _head;
        delete tail;
    }

    void delete_node(const T& data) {
        Node<T>* ptr = _head;
        Node<T>* ptr1 = nullptr;
        do {
            if (ptr->_data == data) {
                if (ptr == _head) {
                    if (ptr->_next == _head) {
                        delete ptr;
                        return;
                    }
                    Node<T>* ptr_last = _head;
                    while (ptr_last->_next != _head) {
                        ptr_last = ptr_last->_next;
                    }
                    _head = ptr->_next;
                    ptr_last->_next = ptr->_next;
                    Node<T>* temp = ptr;
                    ptr = ptr->_next;
                    delete temp;
                }
                else {
                    ptr1->_next = ptr->_next;
                    Node<T>* temp = ptr;
                    ptr = ptr->_next;
                    delete temp;
                }
            }
            else {
                ptr1 = ptr;
                ptr = ptr->_next;
            }
        } while (ptr != _head);
    }

    Node<T>* get_head() const {
        return _head;
    }
};

template<typename T>
struct Term {
    T coefficient;
    int exponent;
    Term(T coeff, int exp) : coefficient(coeff), exponent(exp) {}
};

template<typename T>
class Polynomial {
private:
    LinkedList<Term<T>> terms;

public:
    Polynomial() {}

    void addTerm(const T& coefficient, int exponent) {
        if (coefficient != 0) {
            terms.push_tail(Term<T>(coefficient, exponent));
        }
    }

    T evaluate(T x) const {
        T result = 0;
        Node<Term<T>>* ptr = terms.get_head();
        Node<Term<T>>* ptr_aisd = terms.get_head();
        do {
            result += ptr->_data.coefficient * pow(x, ptr->_data.exponent);
            ptr = ptr->_next;
        } while(ptr != ptr_aisd);
        return result;
    }

    void print() const {
        Node<Term<T>>* ptr = terms.get_head();
        Node<Term<T>>* ptr_head = terms.get_head();
        do {
            std::cout << ptr->_data.coefficient << "x^" << ptr->_data.exponent;
            ptr = ptr->_next;
            if (ptr != ptr_head) {
                std::cout << " + ";
            }
        } while (ptr != ptr_head);
        std::cout << std::endl;
    }
};


int main() {
    Polynomial<double> poly;
    poly.addTerm(2.0, 3);
    poly.addTerm(-1.5, 2);
    poly.addTerm(1.0, 1);
    poly.addTerm(4.5, 0);

    poly.print();

    double x = 2.0;
    double result = poly.evaluate(x);

    std::cout << "x = " << x << " is: " << result << std::endl;

    
    
    
    
    
    LinkedList<int> list;

    list.push_head(3);
    list.push_head(2);
    list.push_head(1);

    list.push_tail(4);
    list.push_tail(5);
    list.push_tail(6);

    cout << "list: ";
    list.print();
    cout << endl;

    Node<int>* head = list.get_head();
    if (head) {
        cout << "Head value: " << head->_data << endl;
    }

    cout << "Element at index 2: " << list[2] << endl;

    list.pop_head();
    list.pop_tail();

    list.delete_node(3);

    cout << "Modified list: ";
    list.print();
    cout << endl;

    return 0;
    
}

