// 
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно 1
// 
// Име: Жени Христова Каракашева
// ФН: 81977
// Специалност: Компютърни науки
// Курс: 2
// Административна група: 4
// Ден, в който се явявате на контролното: 24.04.2021
// Начален час на контролното: 09:30 
// Кой компилатор използвате: GCC
//

#include <cassert>
#include <cstring>
#include <iostream>
#include <string>

#include <cstddef>
#include <cstdlib>
#include <stdexcept>

class IntBuffer {
    int* dataBuffer;
    std::size_t sizeBuffer;
    
    void copy(const IntBuffer& other) {
        int* temp = new(std::nothrow) int[other.sizeBuffer];
       
        if(temp == nullptr) {
           throw std::bad_alloc();
        }
        
        for(std::size_t i = 0; i < other.sizeBuffer; i++) {
            temp[i] = other.dataBuffer[i];
        }

        dataBuffer = temp;
        sizeBuffer = other.sizeBuffer;
    }

    public:
    IntBuffer(std::size_t size) {
        int* temp = nullptr;

        try {
            temp = new(std::nothrow) int[size];

        } catch (const std::bad_alloc& exc) {
            std::cerr<<exc.what()<<std::endl;
        }

        dataBuffer = temp;
        sizeBuffer = size;
    }

    IntBuffer(const IntBuffer& other) {
        copy(other);
    }

    IntBuffer& operator=(const IntBuffer& other) {
        if(this != &other) {
            copy(other);
            delete[] dataBuffer;
        } 

        return *this;
    }

    ~IntBuffer() {
        delete[] dataBuffer;
        sizeBuffer = 0;
    }

    IntBuffer(std::size_t size, const IntBuffer& other) {
        
        int* temp = nullptr;

        try {
            temp = new(std::nothrow) int[size];

        } catch (const std::bad_alloc& exc) {
            std::cerr<<exc.what()<<std::endl;
        }
        
        std::size_t n= 0;

        if(size > other.sizeBuffer) {
            n = other.sizeBuffer;
        } else {
            n = size;
        }

        for(std::size_t i = 0; i < n; i++) {
            try {
                temp[i] = other.dataBuffer[i];
            } catch (const std::bad_alloc& exc) {
                std::cerr<<exc.what()<<std::endl;
            }    
        }

        delete[] dataBuffer;
        dataBuffer = temp;
        sizeBuffer = size;
    }

    int& at(std::size_t index) {
        if(index < 0 || index > sizeBuffer) {
            throw std::out_of_range("An invalid index!");
        }

        return dataBuffer[index];
    }

    const int& at(std::size_t index) const {
        if(index < 0 || index > sizeBuffer) {
            throw std::out_of_range("An invalid index!");
        }

        return dataBuffer[index];
    }

    int& operator[](std::size_t index) {
        assert(index > -1 && index < sizeBuffer);

        return dataBuffer[index];
    }

    const int& operator[](std::size_t index) const {
        assert(index > -1 && index < sizeBuffer);

        return dataBuffer[index];
    }

    std::size_t size() const {
        return sizeBuffer;
    }

    void copy_from(const IntBuffer& other, std::size_t count) {
        if(sizeBuffer < count || other.sizeBuffer < count) {
            throw std::out_of_range("Invalid number for copying!");
        }

        for(std::size_t i = 0; i < count; i++) {
            dataBuffer[i] = other.dataBuffer[i]; 
        }
    }

    bool operator==(const IntBuffer& other) const {
        bool difference = false;

        for(std::size_t i = 0; i < sizeBuffer; i++) {
            if(dataBuffer[i] != other.dataBuffer[i]) {
                difference = true;
            }
        }

        return (sizeBuffer == other.sizeBuffer) && (difference == false);
    }

    bool operator<(const IntBuffer& other) const {
        bool before = true;

        for(std::size_t i = 0; i < other.sizeBuffer; i++) {
            if(dataBuffer[i] > other.dataBuffer[i]) {
                before = false;
            }
        }

        return before;
    }

    friend std::ostream& operator<<(std::ostream& out, const IntBuffer& other) {
        for(std::size_t i = 0; i < other.sizeBuffer; i++) {
            out<<other.dataBuffer[i]<<" ";
        }

        return out;
    }
};

class Set {
    IntBuffer** elements;
    std::size_t used;

    public:
    Set() {
        elements = new (std::nothrow) IntBuffer*[2];

        for(std::size_t i = 0; i < 2; i++) {
            elements[i] = new (std::nothrow) IntBuffer(2);
        }
       
        used = 0;
    }

    void insert(int value) {
        for(std::size_t i = 0; i < used; i++) {
            if(*elements[i] == value) {
                return;
            }
        }

        std::size_t indexToInput = 0;

        for(std::size_t i = 0; i < used; i++) {
            if(!(*elements[i] < value) ) {
                indexToInput = i;
            }
        }

        IntBuffer** temp = new (std::nothrow) IntBuffer*[used*2];

        if(temp == nullptr) {
            throw std::bad_alloc();
        }

        for(std::size_t i = 0; i < indexToInput; i++) {
            temp[i] = elements[i];
        }

        *temp[indexToInput] = value;

        for(std::size_t i = indexToInput+1; i < used; i++) {
            temp[i] = elements[i+1];
        }

        delete[] elements;
        elements = temp;
        used++;
    }

    bool contains(int value) const {
        bool found = false;

        std::size_t separator = used/2;

        do {
            if(*elements[separator] == value) {
                found = true;
            } else if(*elements[separator] < value) {
                separator = (used - separator) / 2;
            } else if (!(*elements[separator] < value) ) {
                separator = (0 + separator) / 2;
            }
        } while( found != true || separator == 0);

        return found;
    }

    std::size_t size() const {
        return used;
    }

    friend std::ostream& operator<<(std::ostream& out, const Set& other) {
        for(std::size_t i = 0; i < other.used; i++) {
            out<<other.elements[i]<<" ";
        }

        return out;
    }
};

int main()
{
    std::size_t n = 0;
    std::cout<<"Please input a valid number: ";
    std::cin>>n;

    Set generated;

    int temp = 0;

    for(std::size_t add = 0; add < n; add++) {
        temp = std::rand();
        generated.insert(temp);
    }

    Set G;

    int guess = 0;

    do {
        std::cout<<"Guess a number from the set: ";
        std::cin>>guess;

        if(generated.contains(guess) == true) {
            G.insert(guess);
        }

    } while(G.size() != generated.size());

    if(G.size() == generated.size() ) {
        std::cout<<"Congratulations! You successfully guessed all the numbers from the set!";
    }

	return 0; 
}