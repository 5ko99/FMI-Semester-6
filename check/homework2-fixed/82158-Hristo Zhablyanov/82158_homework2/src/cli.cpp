#include "cli.h"

vector<string> Cli::read() {
    if (initial_commands.empty()) {
        string input;
        getline(cin, input);
        return split(input);
    }

    vector<string> args = initial_commands.back();
    initial_commands.pop_back();
    return args;
}

vector<string> Cli::split(string& str) const {
    vector<string> args;

    str.erase(0, str.find_first_not_of(' '));
    str.erase(str.find_last_not_of(' ') + 1);
    if (str.empty()) return args;

    unsigned i = 0;
    while (i < str.length()) {
        while (str[i] == ' ') i++;

        int pos = str.find(" ", i);
        if (pos < 0) pos = str.length();
        args.push_back(str.substr(i, pos - i));
        i = pos;
    }

    return args;
}

string Cli::concat(const vector<string>& args, unsigned from, unsigned to) const {
    assert(from < to);
    assert(to <= args.size());

    string str = args[from];
    for (string::size_type i = from + 1; i < to; i++) str.append(" ").append(args[i]);
    return str;
}

unsigned Cli::str_to_u(const string& str) const {
    int num = stoi(str);
    if (num < 0) num = -num;
    return num;
}

void Cli::to_upper(string& str) const {
    int dif = 'A' - 'a';
    for (string::size_type i = 0; i < str.length(); i++)
        if (str[i] >= 'a' && str[i] <= 'z') str[i] += dif;
}

bool Cli::request_confirmation(const char* text) const {
    cout << text << "\nProceed? (y for yes, anything else for no)\n";
    char c;
    cin >> c;
    cin.ignore(1000, '\n');
    return c == 'y';
}

void Cli::save() {
    file.open(path, ios::out);
    if (!file) {
        cout << "Could not load file.\n";
        return;
    }

    container.save(file);
    file.close();
}

Cli::Cli(string _path) : path(_path) {
    file.open(path, ios::in);

    if (file) {
        string input;

        while (!file.eof()) {
            getline(file, input);
            if (input.empty()) break;
            initial_commands.push_back(split(input));
        }

        if (initial_commands.empty()) cout << "No commands were loaded." << endl;

        // Reverse order, so that commands can be popped
        for (unsigned start = 0, end = initial_commands.size() - 1;
             start < initial_commands.size() / 2;
             start++, end--) {
            vector<string> temp = initial_commands[start];
            initial_commands[start] = initial_commands[end];
            initial_commands[end] = temp;
        }
    } else
        cout << "No commands were loaded." << endl;

    file.close();
}

Cli::~Cli() { file.close(); }

void Cli::run() {
    while (true) {
        vector<string> args = read();

        if (args.size() == 0) {
            cout << "No arguments!\n";
            continue;
        }

        to_upper(args[0]);

        if (args[0] == "VEHICLE") {
            if (args.size() < 3) {
                cout << "Not enough arguments!\n";
                continue;
            }

            to_upper(args[1]);

            try {
                Registration r(args[1]);

                if (container.contains(r)) {
                    cout << "Vehicle with registration " << r << " already exists!\n";
                    continue;
                }

                string desc = concat(args, 2, args.size());

                container.push(r, desc);
                continue;
            } catch (invalid_argument& e) {
                cout << "Bad registration: " << e.what() << endl;
                continue;
            }
        } else if (args[0] == "PERSON") {
            if (args.size() < 3) {
                cout << "Not enough arguments!\n";
                continue;
            }

            unsigned id = str_to_u(args[args.size() - 1]);

            if (container.contains(id)) {
                cout << "Person with id " << id << " already exists!\n";
                continue;
            }

            string name = concat(args, 1, args.size() - 1);

            container.push(id, name);
            continue;
        } else if (args[0] == "ACQUIRE") {
            if (args.size() != 3) {
                cout << "This command accepts exactly 2 arguments!\n";
                continue;
            }

            unsigned id = str_to_u(args[1]);

            if (!container.contains(id)) {
                cout << "No person with id " << id << endl;
                continue;
            }

            to_upper(args[2]);

            try {
                Registration r(args[2]);

                if (!container.contains(r)) {
                    cout << "No vehicle with registration " << r << endl;
                    continue;
                }

                container.acquire(id, r);
                continue;
            } catch (invalid_argument& e) {
                cout << "Bad vehicle: " << e.what() << endl;
                continue;
            } catch (range_error& e) {
                cout << "Missing: " << e.what() << endl;
                continue;
            }
        } else if (args[0] == "RELEASE") {
            if (args.size() != 3) {
                cout << "This command accepts exactly 2 arguments!\n";
                continue;
            }

            unsigned id = str_to_u(args[1]);

            if (!container.contains(id)) {
                cout << "No person with id " << id << endl;
                continue;
            }

            to_upper(args[2]);

            try {
                Registration r(args[2]);

                if (!container.contains(r)) {
                    cout << "No vehicle with registration " << r << endl;
                    continue;
                }

                container.release(id, r);
                continue;
            } catch (invalid_argument& e) {
                cout << "Bad registration: " << e.what() << endl;
                continue;
            } catch (range_error& e) {
                cout << "Missing: " << e.what() << endl;
                continue;
            }
        } else if (args[0] == "REMOVE") {
            if (args.size() != 2) {
                cout << "This command accepts exactly 1 argument!\n";
                continue;
            }

            unsigned id;
            bool is_person = true;
            try {
                id = str_to_u(args[1]);
            } catch (invalid_argument& e) {
                is_person = false;
            }

            if (is_person) {
                if (!container.contains(id)) {
                    cout << "No person with id " << id << endl;
                    continue;
                }

                if (container.is_dependant(id) &&
                    !request_confirmation("This person owns vehicles!"))
                    continue;

                container.remove(id);
                continue;
            }

            to_upper(args[1]);

            try {
                Registration r(args[1]);

                if (!container.contains(r)) {
                    cout << "No vehicle with registration " << r << endl;
                    continue;
                }

                if (container.is_dependant(r) &&
                    !request_confirmation("This vehicle has an owner!"))
                    continue;

                container.remove(r);
                continue;
            } catch (invalid_argument& e) {
                cout << "Not a valid id/registration\n";
                continue;
            }
        } else if (args[0] == "SHOW") {
            if (args.size() != 2) {
                cout << "This command accepts exactly 1 argument!\n";
                continue;
            }

            to_upper(args[1]);

            if (args[1] == "PEOPLE") {
                container.print_people();
                continue;
            }

            if (args[1] == "VEHICLES") {
                container.print_vehicles();
                continue;
            }

            unsigned id;
            bool is_person = true;
            try {
                id = str_to_u(args[1]);
            } catch (invalid_argument& e) {
                is_person = false;
            }

            if (is_person) {
                if (!container.contains(id)) {
                    cout << "No person with id " << id << endl;
                    continue;
                }

                container.print(id);
                continue;
            }

            to_upper(args[1]);

            try {
                Registration r(args[1]);

                if (!container.contains(r)) {
                    cout << "No vehicle with registration " << r << endl;
                    continue;
                }

                container.print(r);
                continue;
            } catch (invalid_argument& e) {
                cout << "Not a valid id/registration\n";
                continue;
            }
        } else if (args[0] == "SAVE")
            save();
        else if (args[0] == "END")
            return;
        else
            cout << "Unknown command!\n";
    }
}
