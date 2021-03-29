#include <iostream>
#include "List.h"
using std::cin;
using std::cout;
using std::endl;
int main() {
    List list;
//    int n;
//    cin>>n;
//    for(int i=0;i<n;++i) {
//        int temp;
//        cin>>temp;
//        list.insertBegin(temp);
//    }
    list.insertBegin(2),list.insertBegin(8),list.insertBegin(9);
    cout<<list[0]<<endl;
    list.deleteEnd();
    list.print();
    cout<<"end\n";
    return 0;
}
