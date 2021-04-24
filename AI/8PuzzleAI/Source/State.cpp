#include "State.h"
#include <random>
#include<stdexcept>

State::State() {
   for(short i=0;i<SIZE;++i)
       state[i] = i;
}

State::State(const std::array<short, SIZE> &other) : state(other) {}

State::State(std::array<short, 9>&& other) : state(other) {

}

State::State(bool randomizeFlag) {
    for(short i=0;i<SIZE;++i)
        state[i] = i;
    if(randomizeFlag) {
        randomize();
    }
}


//State & State::operator=(const State &other) {
//    if(this != &other) {
//        state = other.state;
//    }
//    return *this;
//}
//
//State & State::operator=(State &&other)  noexcept {
//    if(this != &other) {
//        state = other.state;
//    }
//    return *this;
//}
//
//State::State(State &&other) noexcept : state(other.state) {}

bool operator==(const State &lhs, const State &rhs) {
    return lhs.state == rhs.state;
}

bool operator!=(const State &lhs, const State &rhs) {
    return !(lhs==rhs);
}

bool operator>(const State &lhs, const State &rhs) {
    return lhs.state < rhs.state;
}

const std::array<short, 9> & State::getArray() const {
    return state;
}

void State::setArray(const std::array<short, 9> &arr) {
    state = arr;
}

void State::setArray(std::array<short, 9> &&arr) {
    state = arr;
}

short State::findEmptyTile() const {
    for(short i=0;i<SIZE;++i)
        if(state[i]==EMPTY_TILE) return i;
    throw std::invalid_argument("Invalid board without empty!");
}

bool State::isAdjWithEmpty(short pos,short emptyPos) {
    if(pos==emptyPos) return false;
    short directions[4];//0-up,1-down,2-left,3-right
    directions[0] = pos-3>=0 ? pos - 3 : -1;
    directions[1] = pos+3<SIZE ? pos + 3 : -1;
    directions[2] = (pos-1)>= 0 && pos % ROWS !=0  ? pos-1 : -1;
    directions[3] = (pos+1)<SIZE && pos % ROWS != 2 ? pos+1:-1;
    for(short dir : directions)
        if(dir!=-1 && dir==emptyPos) return true;
    return false;
}

void State::swapWithEmpty(short pos) {
    short emptyPos = findEmptyTile();
    if(isAdjWithEmpty(pos,emptyPos))
        swap(pos,emptyPos);
}

void State::swap(short i, short j) {
    short temp = state[i];
    state[i] = state[j];
    state[j] = temp;
}

short State::manhattanCost() const {
    short cost = 0;
    for(short i=0;i<SIZE;++i) {
        short row = (state[i]-1) / ROWS;
        short col = (state[i]-1) % COLS;

        short finalRow = i / ROWS;
        short finalCol = i % COLS;

        short manCost = abs(row-finalRow) + abs(col-finalCol);
        cost+=manCost;
    }
    return cost;
}

short State::hammingCost() const{
    short cost = 0;
    for(short i=0;i<SIZE;++i) {
        if(state[i] != i) cost++;
    }
    return cost;
}

void State::randomize() {
    std::shuffle(state.begin(),state.end(), std::mt19937(std::random_device()()));
}

void State::printState(std::ostream &stream) const {
    for(short row=0;row<ROWS;++row) {
        for(short col=0;col<COLS;++col) {
            short index = row * ROWS + col;
            stream<<state[index]<<' ';
        }
        stream<<'\n';
    }
    stream<<' ';
}

