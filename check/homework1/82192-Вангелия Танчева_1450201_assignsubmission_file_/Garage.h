#ifndef GARAGE_H_INCLUDED
#define GARAGE_H_INCLUDED

class Garage
{
private:
    size_t garage_size;
    Vehicle* vehicles;

public:
    ///Constructor with argument
    Garage(size_t garage_size);

    //~Garage();

    void insert(Vehicle& v);

    void erase(const char* registration);

    const Vehicle& at(size_t pos) const;

    const Vehicle& operator[](size_t pos) const;

    bool empty() const;

    size_t size() const;

    void clear();

    const Vehicle* find(const char* registration) const;

    void print();
};

#endif // GARAGE_H_INCLUDED
