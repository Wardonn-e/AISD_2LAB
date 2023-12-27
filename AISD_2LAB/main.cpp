#include <iostream>
#include <cstdlib>

using namespace std;
template<typename T>
struct Term {
    T coefficient;
    int exponent;

    Term(T coeff, int exp = 1) {
        coefficient = coeff;
        exponent = exp;
    }
    
};
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
    void push(const T& data, int in_head){
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
        if (in_head){
            _head = new_head;
        }
    }
public:
    LinkedList() : _head(nullptr) {}
    
    
    LinkedList(size_t size, T min_value, T max_value) : _head(nullptr) {
        for (size_t i = 0; i < size; ++i) {
            T random_value = (rand() % (max_value - min_value + 1) + min_value);
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
    
    void push_head(const int& data) {
        push(data, 1);
    }
    void push_tail(const int& data) {
        push(data, 0);
    }
    
    void push_head(const Term<int>& data) {
        if (data.coefficient != 0) push(data, 1);
    }
    
    void push_tail(const Term<int>& data) {
        if (data.coefficient != 0) push(data, 0);
    }
    
   
    
    void push_head(const LinkedList& a) {
        LinkedList temp(a);
        temp.push_tail(*this);
        swap(temp);
        
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

    // Метод для вывода узлов типа Term
    void printTerms() const {
        Node<T>* ptr = _head;
        Node<T>* ptr_head = _head;
        do {
            std::cout << ptr->_data.coefficient << "x^" << ptr->_data.exponent;
            ptr = ptr->_next;
            if (ptr != ptr_head) {
                std::cout << " + ";
            }
        } while (ptr != ptr_head);
        std::cout << std::endl;
    }
    
    double evaluate(double x) const {
        double result = 0;
        Node<T>* ptr = _head;
        Node<T>* ptr_aisd = _head;
        do {
            result += ptr->_data.coefficient * pow(x, ptr->_data.exponent);
            ptr = ptr->_next;
        } while(ptr != ptr_aisd);
        return result;
    }
    
    const T& operator[](int index) const {
        if (index < 0) {
            throw std::out_of_range("Negative index");
        }
        Node<T>* ptr = _head;
        for (int i = 0; i < index; i++) {
            ptr = ptr->_next;
            if (ptr == _head) {
                throw std::out_of_range("Index out of range");
            }
        }
        return ptr->_data;
    }

    T& operator[](int index) {
        if (index < 0) {
            throw std::out_of_range("Negative index");
        }
        Node<T>* ptr = _head;
        for (int i = 0; i < index; i++) {
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

    void delete_node(const int& data) {
        Node<T>* ded_node = new Node(data);
        Node<T>* current = _head;

        while (current->_next != _head) {
            if (current->_next->_data == data) {
                Node<T>* repair_node = current->_next->_next;
                delete current->_next;
                current->_next = repair_node;
            }
            else
                current = current->_next;
        }
        if (_head->_data == data)
            pop_head();

    }
    void delete_node(const Term<int>& data) {
        Node<T>* ded_node = new Node(data);
        Node<T>* current = _head;

        while (current->_next != _head) {
            if (current->_next->_data.coefficient == data.coefficient && current->_next->_data.exponent == data.exponent) {
                Node<T>* repair_node = current->_next->_next;
                delete current->_next;
                current->_next = repair_node;
            }
            else
                current = current->_next;
        }
        if (_head->_data.exponent == data.exponent && _head->_data.coefficient == data.coefficient)
            pop_head();
    }



    Node<T>* get_head() const {
        return _head;
    }
};

int main() {
    LinkedList<Term<int>> l;
    Term<int> l1(2,2);
    Term<int> l2(3,2);
    Term<int> l3(4,2);
    l.push_head(l1);
    l.push_head(l2);
    l.push_tail(l2);
    l.push_head(l3);
    l.delete_node(l2);
    l.printTerms();
    
    LinkedList<int> list1;
    list1.push_tail(1);
    list1.push_tail(2);
    list1.push_tail(3);
    list1.push_head(2);
    list1.push_tail(2);
    list1.delete_node(2);
    list1.print();


    return 0;
}
