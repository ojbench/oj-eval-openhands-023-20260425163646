
#include <iostream>
#include <stdexcept>

namespace sjtu {

template<typename T>
class deque {
private:
    T* data;
    size_t front_index;
    size_t back_index;
    size_t capacity;
    size_t current_size;

    void resize() {
        size_t new_capacity = std::max(static_cast<size_t>(8), capacity * 2);
        T* new_data = new T[new_capacity];
        
        // Copy elements to new array
        for (size_t i = 0; i < current_size; ++i) {
            new_data[i] = data[(front_index + i) % capacity];
        }
        
        delete[] data;
        data = new_data;
        front_index = 0;
        back_index = current_size;
        capacity = new_capacity;
    }

public:
    // Iterator class
    class iterator {
    private:
        T* ptr;
        deque* container;
        size_t index;
        
    public:
        iterator() : ptr(nullptr), container(nullptr), index(0) {}
        iterator(T* p, deque* c, size_t i) : ptr(p), container(c), index(i) {}
        
        T& operator*() const {
            return *ptr;
        }
        
        iterator& operator++() {
            if (ptr != nullptr && container != nullptr) {
                ptr = &container->data[(index + 1) % container->capacity];
                index++;
            }
            return *this;
        }
        
        iterator operator++(int) {
            iterator tmp = *this;
            ++(*this);
            return tmp;
        }
        
        iterator& operator--() {
            if (ptr != nullptr && container != nullptr) {
                ptr = &container->data[(index == 0 ? container->capacity - 1 : index - 1) % container->capacity];
                index--;
            }
            return *this;
        }
        
        iterator operator--(int) {
            iterator tmp = *this;
            --(*this);
            return tmp;
        }
        
        bool operator==(const iterator& other) const {
            return ptr == other.ptr;
        }
        
        bool operator!=(const iterator& other) const {
            return ptr != other.ptr;
        }
    };

    // Const iterator class
    class const_iterator {
    private:
        const T* ptr;
        const deque* container;
        size_t index;
        
    public:
        const_iterator() : ptr(nullptr), container(nullptr), index(0) {}
        const_iterator(const T* p, const deque* c, size_t i) : ptr(p), container(c), index(i) {}
        
        const T& operator*() const {
            return *ptr;
        }
        
        const_iterator& operator++() {
            if (ptr != nullptr && container != nullptr) {
                ptr = &container->data[(index + 1) % container->capacity];
                index++;
            }
            return *this;
        }
        
        const_iterator operator++(int) {
            const_iterator tmp = *this;
            ++(*this);
            return tmp;
        }
        
        const_iterator& operator--() {
            if (ptr != nullptr && container != nullptr) {
                ptr = &container->data[(index == 0 ? container->capacity - 1 : index - 1) % container->capacity];
                index--;
            }
            return *this;
        }
        
        const_iterator operator--(int) {
            const_iterator tmp = *this;
            --(*this);
            return tmp;
        }
        
        bool operator==(const const_iterator& other) const {
            return ptr == other.ptr;
        }
        
        bool operator!=(const const_iterator& other) const {
            return ptr != other.ptr;
        }
    };

    // Default constructor
    deque() : front_index(0), back_index(0), capacity(8), current_size(0) {
        data = new T[capacity];
    }

    // Copy constructor
    deque(const deque& other) : front_index(0), back_index(0), capacity(other.capacity), current_size(other.current_size) {
        data = new T[capacity];
        for (size_t i = 0; i < current_size; ++i) {
            data[i] = other.data[(other.front_index + i) % other.capacity];
        }
    }

    // Assignment operator
    deque& operator=(const deque& other) {
        if (this != &other) {
            delete[] data;
            capacity = other.capacity;
            current_size = other.current_size;
            data = new T[capacity];
            front_index = 0;
            back_index = current_size;
            for (size_t i = 0; i < current_size; ++i) {
                data[i] = other.data[(other.front_index + i) % other.capacity];
            }
        }
        return *this;
    }

    // Destructor
    ~deque() {
        delete[] data;
    }

    bool empty() const {
        return current_size == 0;
    }

    size_t size() const {
        return current_size;
    }

    void push_front(const T& value) {
        if (current_size == capacity) {
            resize();
        }
        
        front_index = (front_index == 0) ? capacity - 1 : front_index - 1;
        data[front_index] = value;
        ++current_size;
    }

    void push_back(const T& value) {
        if (current_size == capacity) {
            resize();
        }
        
        data[back_index] = value;
        back_index = (back_index + 1) % capacity;
        ++current_size;
    }

    void pop_front() {
        if (empty()) {
            throw std::runtime_error("pop_front on empty deque");
        }
        
        front_index = (front_index + 1) % capacity;
        --current_size;
    }

    void pop_back() {
        if (empty()) {
            throw std::runtime_error("pop_back on empty deque");
        }
        
        back_index = (back_index == 0) ? capacity - 1 : back_index - 1;
        --current_size;
    }

    T& front() {
        if (empty()) {
            throw std::runtime_error("front on empty deque");
        }
        return data[front_index];
    }

    const T& front() const {
        if (empty()) {
            throw std::runtime_error("front on empty deque");
        }
        return data[front_index];
    }

    T& back() {
        if (empty()) {
            throw std::runtime_error("back on empty deque");
        }
        return data[(back_index == 0) ? capacity - 1 : back_index - 1];
    }

    const T& back() const {
        if (empty()) {
            throw std::runtime_error("back on empty deque");
        }
        return data[(back_index == 0) ? capacity - 1 : back_index - 1];
    }

    // Subscript operator
    T& operator[](size_t n) {
        return data[(front_index + n) % capacity];
    }

    const T& operator[](size_t n) const {
        return data[(front_index + n) % capacity];
    }

    // At method with bounds checking
    T& at(size_t n) {
        if (n >= current_size) {
            throw std::out_of_range("index out of range");
        }
        return data[(front_index + n) % capacity];
    }

    const T& at(size_t n) const {
        if (n >= current_size) {
            throw std::out_of_range("index out of range");
        }
        return data[(front_index + n) % capacity];
    }

    // Insert element at position
    iterator insert(iterator pos, const T& value) {
        size_t index = pos.index;
        
        if (current_size == capacity) {
            resize();
        }
        
        // Shift elements to make room
        if (index < current_size / 2) {
            // Shift front elements forward
            front_index = (front_index == 0) ? capacity - 1 : front_index - 1;
            for (size_t i = 0; i < index; ++i) {
                data[(front_index + i) % capacity] = data[(front_index + i + 1) % capacity];
            }
        } else {
            // Shift back elements backward
            for (size_t i = current_size; i > index; --i) {
                data[(front_index + i) % capacity] = data[(front_index + i - 1) % capacity];
            }
            if (back_index == 0) {
                back_index = capacity - 1;
            } else {
                back_index--;
            }
        }
        
        data[(front_index + index) % capacity] = value;
        ++current_size;
        
        return iterator(&data[(front_index + index) % capacity], this, index);
    }

    // Erase element at position
    iterator erase(iterator pos) {
        if (empty()) {
            throw std::runtime_error("erase on empty deque");
        }
        
        size_t index = pos.index;
        T* result_ptr;
        
        // Shift elements to fill the gap
        if (index < current_size / 2) {
            // Shift front elements backward
            for (size_t i = index; i > 0; --i) {
                data[(front_index + i) % capacity] = data[(front_index + i - 1) % capacity];
            }
            result_ptr = &data[front_index];
            if (front_index == capacity - 1) {
                front_index = 0;
            } else {
                front_index++;
            }
        } else {
            // Shift back elements forward
            for (size_t i = index; i < current_size - 1; ++i) {
                data[(front_index + i) % capacity] = data[(front_index + i + 1) % capacity];
            }
            result_ptr = &data[(front_index + index) % capacity];
            if (back_index == 0) {
                back_index = capacity - 1;
            } else {
                back_index--;
            }
        }
        
        --current_size;
        
        return iterator(result_ptr, this, index);
    }

    iterator begin() {
        return iterator(&data[front_index], this, 0);
    }

    iterator end() {
        return iterator(&data[back_index], this, current_size);
    }

    const_iterator cbegin() const {
        return const_iterator(&data[front_index], this, 0);
    }

    const_iterator cend() const {
        return const_iterator(&data[back_index], this, current_size);
    }

    const_iterator begin() const {
        return cbegin();
    }

    const_iterator end() const {
        return cend();
    }
};

} // namespace sjtu

int main() {
    sjtu::deque<int> dq;
    std::string command;
    
    while (std::cin >> command) {
        if (command == "push_front") {
            int value;
            std::cin >> value;
            dq.push_front(value);
        } else if (command == "push_back") {
            int value;
            std::cin >> value;
            dq.push_back(value);
        } else if (command == "pop_front") {
            if (dq.empty()) {
                std::cout << "error" << std::endl;
            } else {
                std::cout << dq.front() << std::endl;
                dq.pop_front();
            }
        } else if (command == "pop_back") {
            if (dq.empty()) {
                std::cout << "error" << std::endl;
            } else {
                std::cout << dq.back() << std::endl;
                dq.pop_back();
            }
        } else if (command == "front") {
            if (dq.empty()) {
                std::cout << "error" << std::endl;
            } else {
                std::cout << dq.front() << std::endl;
            }
        } else if (command == "back") {
            if (dq.empty()) {
                std::cout << "error" << std::endl;
            } else {
                std::cout << dq.back() << std::endl;
            }
        } else if (command == "size") {
            std::cout << dq.size() << std::endl;
        } else if (command == "empty") {
            std::cout << (dq.empty() ? "1" : "0") << std::endl;
        }
    }
    
    return 0;
}
