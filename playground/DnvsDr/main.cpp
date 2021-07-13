#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

unsigned g(unsigned x, unsigned y);

unsigned f(unsigned x)
{
    if (x == 0)
        return f(g(x, f(x)));
    else
        return 0;
}

unsigned g(unsigned x, unsigned y)
{
    if (x == 0)
        return 0;
    else
        return g(f(x), y);
}

//0 for every x>0
//undefined x=0
unsigned func(unsigned x)
{
    return g(x, f(x));
}

int main()
{
    unsigned input;
    cout << "Input=";
    cin >> input;
    unsigned result = func(input);
    cout << "Result=" << result << endl;
    return 0;
}