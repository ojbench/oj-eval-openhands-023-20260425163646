
#include <iostream>
#include <vector>
#include <stdexcept>

template<typename T>
class Deque {
private:
    std::vector<T> data;
    size_t front_index;
    size_t back_index;
    size_t capacity;
    size_t current_size;

    void resize() {
        size_t new_capacity = std::max(static_cast<size_t>(8), capacity * 2);
        std::vector<T> new_data(new_capacity);
        
        // Copy elements to new array
        for (size_t i = 0; i < current_size; ++i) {
            new_data[i] = data[(front_index + i) % capacity];
        }
        
        data = std::move(new_data);
        front_index = 0;
        back_index = current_size;
        capacity = new_capacity;
    }

public:
    Deque() : front_index(0), back_index(0), capacity(8), current_size(0) {
        data.resize(capacity);
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
};

int main() {
    Deque<int> dq;
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
