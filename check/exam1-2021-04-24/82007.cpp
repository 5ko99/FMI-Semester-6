// 
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно 1
// 
// Име: Теодор Кехайов
// ФН: 82007
// Специалност: Компютърни науки
// Курс: Втори
// Административна група: Първа
// Ден, в който се явявате на контролното: 24.04.2021
// Начален час на контролното:
// Кой компилатор използвате: GCC
//


#define _CRT_SECURE_NO_WARNINGS 

#include <cassert>
#include <cstring>
#include <iostream>
#include <string>

class IntBuffer
{
private:
    std::size_t size;
    int*array;

public:
    IntBuffer(std::size_t size): size(size)
    {
        array=new int[size];
    }

    IntBuffer(const IntBuffer& b):size(b.size)
    {
        memcpy(this->array,b.array,size);
    }

    IntBuffer& operator=(const IntBuffer& b)
    {
        if(this!=&b)
        {
            delete this;
            this->size=b.size;
            for (int i = 0; i < size; i++) {
                this->array[i] = b.array[i];
            }
        }

        return *this;
    }

    ~IntBuffer(){ delete[] array; }

    IntBuffer(std::size_t size, const IntBuffer& other):size(size)
    {
        array=new int[size];
        std::size_t N;
        if(size<other.size) N=size;
        else N=other.size;

        for (int i = 0; i < N; ++i)
        {
            array[i]=other.array[i];
        }
    }

    int& at(std::size_t index)
    {
        if(index<0 || index>this->size-1) throw std::out_of_range("Incorrect index!");
        return array[index];
    }

    const int& at(std::size_t index) const
    {
        if(index<0 || index>this->size-1) throw std::out_of_range("Incorrect index!");
        return array[index];
    }

    int& operator[](std::size_t index) noexcept
    {
        return array[index];
    }

    const int& operator[](std::size_t index) const noexcept
    {
        return array[index];
    }

    std::size_t Size() const
    {
        return this->size;
    }

    void copy_from(const IntBuffer& other, std::size_t count)
    {
        if(count>this->size || count>other.size)
            throw std::out_of_range("mistake in copy_from");

        for (int i = 0; i < count; i++) {
            this->array[i]=other.array[i];
        }
    }

    bool operator==(const IntBuffer& other) const
    {
        if(this->size==other.size)
        {
            int temp=0;
            for (int i = 0; i < size; i++)
            {
                if(array[i]==other.array[i]) temp++;
            }
            if(temp==size) return true;
        }
     return false;
    }

    bool operator<(const IntBuffer& other) const
    {
        return memcmp(this->array,other.array,size);
    }

};




class Set
{
private:
    std::size_t MAX_CAPACITY;
    std::size_t counter;
    IntBuffer elements;


public:
    Set(): counter(0), MAX_CAPACITY(2), elements(MAX_CAPACITY)
    {
        if(counter==MAX_CAPACITY) {
            MAX_CAPACITY *= 2;
            elements=IntBuffer(MAX_CAPACITY);
        }
    }



    void insert(int value) noexcept
    {
        if(contains(value)) return;

        IntBuffer temp(this->size()+1);

        for (int i = 0; i < MAX_CAPACITY; i++)
        {
            if(value<elements[i])
            {
                temp.copy_from(elements,i);
                temp[i]=value;
                for(int j=i+1;j<MAX_CAPACITY-1;j++)
                {
                    temp[j]=elements[j+1];
                }
                continue;
            }
        }

        elements.copy_from(temp,temp.Size());
        counter++;
    }

    void print() const
    {
        for (int i = 0; i < size(); i++) {
            std::cout<<elements[i];
        }
    }

    bool contains(int value) const
    {
        for (int i = 0; i < counter; i++)
        {
            if(elements[i]==value) return true;
        }
        return false;
    }

    std::size_t size() const
    {
        return counter;
    }
};

int main()
{
    std::size_t N;
    std::cin>>N;

    Set generated;
    for(int i=0;i<N;i++)
    {
        generated.insert(std::rand());
    }

    std::size_t counter=0;
    do {
        int temp;
        std::cin>>temp;

        if(generated.contains(temp)) counter++;

    } while (counter==N);

	return 0;
}