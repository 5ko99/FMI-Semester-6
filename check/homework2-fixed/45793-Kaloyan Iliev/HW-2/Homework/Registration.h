#ifndef REG_H
#define REG_H

class Registration {
public:
    Registration();
    Registration(const string& number);
    bool operator==(const Registration& other) const;
    friend ostream& operator<<(ostream& out, const Registration& reg);

    bool isValid();
    string getNumber();

private:
    string number;
};

#endif
