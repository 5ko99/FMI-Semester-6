
#ifndef __VECTOR_H
#define __VECTOR_H

#include <iostream>
#include "vehicle.h"

class Vector
{
    private:
    Vehicle** vehicles;
    size_t size;

    public:

    Vector ();
    Vector (const Vector& other);


    Vector (size_t initial_size);
    void to_end (Vehicle& x);

    Vehicle& operator [] (size_t i);
    Vehicle operator [] (size_t i) const;
    Vector& operator = (const Vector& other);
    ~Vector ();
    size_t length () const;
    bool operator != (const Vector& other) const;
    bool operator == (const Vector& other) const;

    private:
    void resize(size_t new_size);

};


std::ostream& operator << (std::ostream& stream, const Vector& v);

#endif