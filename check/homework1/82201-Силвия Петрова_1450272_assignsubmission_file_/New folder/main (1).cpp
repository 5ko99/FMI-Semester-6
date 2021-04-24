#include <iostream>
#include "Garage.h"
#include "VehicleAllocator.h"

using std::cin;
using std::cout;
using std::endl;

/* Function: main
 * ---------------- 
 * Task: програма, която позволява на потребителя да създаде гараж 
 * с избран от него капацитет. След това програмата трябва да позволи 
 * в него да се добавят и премахват превозни средства. Да има и 
 * операция, която извежда съдържанието на гаража на екрана.
 */


void resize(char* &str, size_t& size);
char* insertText();

int main(){

    size_t capacity;
    cout << "Enter capacity of garage: ";
    cin >> capacity;
    Garage gar(capacity);
    VehicleAllocator valloc;

    int num = 0;


    int x = 0;
    while (x != 4)
    {
        cout << "What do you want to do? " << endl;
        cout << "1. Insert Vehicle; 2. Erase Vehicle; 3. Print contents of Garage; 4. End " << endl;
        cin >> x;
        cin.ignore();

        char * registartion;
        char * description;
        size_t space;

        Vehicle veh();
        switch (x)
        {
            case 1:
            {   
                cout << "You choose 1. Insert Vehicle" << endl;

                cout << "Insert licence plate: ";
                registartion = insertText();
                

                cout << "Insert description: ";
                description = insertText();
                

                cout << "Insert space: ";
                cin >> space;

                Vehicle veh = valloc.allocate(registartion, description, space); //това не трябва да е така, затва не става
                gar.insert(veh);
        
                break;
            }
            case 2:  
            {
                cout << "You choose 2. Erase Vehicle" << endl;
                cout << "Insert licence plate: ";
                registartion = insertText();
                

                gar.erase(registartion);
                break;
            }
            case 3:  
            { 
                cout << "You choose 3. Print contents of Garage" << endl;
                gar.print();
                break;
            }
            case 4: 
            { 
                cout << "Bye. Have a nice day :)" << endl;
                break;
            }
            default:
            {
                "Incorrect number :(. Enter Again"; 
                break;
            }
        }
        cout << endl;
    }


    //// works
    // Garage gar(3);
    // VehicleAllocator valloc;
    // Vehicle vuh1 = valloc.allocate("res1", "des1", 1);
    // Vehicle vuh2 = valloc.allocate("res2", "des2", 1);

    // gar.insert(vuh1);
    // gar.insert(vuh2);

    
    // cout << endl;
    // gar.print();


    
    return 0;
}



// from УП seminar
void resize(char* &str, size_t& size) {
    char* oldStr = str;
    str = new char[size*2];

    for (int i = 0; i < size; i++) {
        str[i] = oldStr[i];
    }
    size *= 2;
    delete[] oldStr;
}

char* insertText() {
    size_t size = 2, counter = 0;
    char* text = new char [size]{};

    char symbol;
    cin.get(symbol);
    while (symbol != '\n') {
        if (counter >= size - 1) {
            resize(text, size);
        }
        text[counter++] = symbol;
        cin.get(symbol);
    } 

    text[counter] = '\0';

    return text;
}