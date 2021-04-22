#include <iostream>

class Random {
private:
    float number = 0.5f;
    float number2 = 0.5f;

    Random() = default;

public:
    Random(const Random &) = delete;

    Random &operator=(const Random &) = delete;

    static Random &get() {
        static Random instance;
        return instance;
    }

    static float getFloat() {
        return get().iGetFloat();
    }

    static void setNumbers(float x, float y) {
        get().iSetNumbers(x, y);
    }

private:
    float iGetFloat() const { return number; } //internal

    void iSetNumbers(float x, float y) {
        number = x;
        number2 = y;
    }
};

namespace RandomNamespace {
    static float number = 0.05f;

    static float getFloat() {
        return number;
    }
}

class Static {
public:
    inline static int x;
    int y;

    Static() : y(0) {
        x = 0;
    }

    void print() const {
        std::cout << x << ' ' << y << std::endl;
    }

    static void setX(int _x) {
        x = _x;
    }
};

int main() {
    float number = Random::getFloat();
    std::cout << number << std::endl;
    Random::setNumbers(0.33f,0.33);
    std::cout<<Random::getFloat()<<std::endl;
    std::cout << RandomNamespace::getFloat() << std::endl;

    std::cout << std::endl;
    Static s1;
    Static s2;

    Static::x = 2;
    Static::x = 3;
    std::cout << Static::x << ' ' << Static::x << '\n';
    s1.print();
    Static::setX(22);
    return 0;
}
