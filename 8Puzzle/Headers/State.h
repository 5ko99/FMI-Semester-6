#pragma once
#include<array>
#include<iostream>
#define SIZE 9
#define ROWS 3
#define COLS 3
#define EMPTY_TILE 0
class State {
    std::array<short, SIZE> state{};
public:
    explicit State(const std::array<short, SIZE> &other);

    explicit State(std::array<short,SIZE>&& other);

    explicit State(bool randomize);

//    explicit State(State&& other) noexcept;

    State();

//    State& operator=(const State& other);
//    State& operator=(State&& other) noexcept;

    friend bool operator==(const State &lhs, const State &rhs);
    friend bool operator!=(const State &lhs, const State &rhs);

    short findEmptyTile() const;

    void swapWithEmpty(short i);

    short manhattanCost() const;

    short hammingCost() const;

    void randomize();

    const std::array<short,SIZE>& getArray() const;

    void setArray(const std::array<short,SIZE>& arr);

    void setArray(std::array<short,SIZE>&& arr);

    void printState(std::ostream& stream) const;

private:
    static bool isAdjWithEmpty(short i, short emptyPos);
    void swap(short i,short j);
};

