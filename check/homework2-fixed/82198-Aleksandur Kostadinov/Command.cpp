#include <cmath>
#include "Commands.h"

bool Commands::is_running = true;

const std::string Commands::list_of_commands[9] =
    {"SAVE", "PERSON", "VEHICLE", "ACQUIRE", "RELEASE", // Try to upper case all of them
     "SHOW", "REMOVE", "COMMANDS", "END"};              // command member break into 2 strings which will show the number of parameteres for each command

Commands::Commands(std::string command)
{

    size_t i = 0;
    while (command[i] != ' ' && i < command.size())
    {
        command_type.push_back(Validation::to_upper(command[i]));
        i++;
    }
    try
    {

        if (!is_valid_command())
        {
            throw std::invalid_argument("");
        }
    }
    catch (std::invalid_argument)
    {
        std::cerr << "Invalid command!" << '\n';
    }

    i++;
    if (command[i] == '"')
    {
        i++;
        while (command[i] != '"' && i < command.size())
        {
            command_specification1.push_back(command[i]);
            i++;
        }
        i++;
    }
    else
    {
        while (command[i] != ' ' && i < command.size())
        {
            command_specification1.push_back(command[i]);
            i++;
        }
    }

    i++;

    while (command[i] != ' ' && i < command.size())
    {
        command_specification2.push_back(command[i]);
        i++;
    }
}

bool Commands::is_valid_command() const
{

    for (size_t i = 0; i < 9; i++)
    {
        if (command_type == list_of_commands[i])
        {
            return true;
        }
    }

    return false;
}

void Commands::do_command()
{
    if (command_type == list_of_commands[1])
    {
        do_Person();
    }
    else if (command_type == list_of_commands[2])
    {
        do_Vehicle();
    }
    else if (command_type == list_of_commands[3])
    {
        do_Acquire();
    }
    else if (command_type == list_of_commands[4])
    {
        do_Release();
    }
    else if (command_type == list_of_commands[5])
    {
        do_Show();
    }
    else if (command_type == list_of_commands[6])
    {
        do_Remove();
    }
    else if (command_type == list_of_commands[0])
    {
        do_Save();
    }
    else if (command_type == list_of_commands[7])
    {
        do_Commands();
    }
    else if (command_type == list_of_commands[8])
    {
        do_End();
    }
}

void Commands::do_Person()
{
    size_t i = 0;
    unsigned int id = 0;
    try
    {
        id = std::stoi(command_specification2);
    }
    catch (...)
    {
        id = 0;
    }

    Person person(command_specification1, id);
}

void Commands::do_Vehicle()
{
    Vehicle vehicle(command_specification1, command_specification2);
}

void Commands::do_Acquire()
{
    try
    {
        if (search_for_person() && search_for_vehicle())
        {
            if (search_for_vehicle()->is_free())
            {
                search_for_vehicle()->add_owner(*search_for_person());
                std::cout << search_for_person()->get_name() << " has acquired " << search_for_vehicle()->get_desc() << " "
                          << command_specification2 << "!\n";
            }
            else
            {
                if (search_for_vehicle()->get_owner() != search_for_person())
                {
                    std::cout << search_for_vehicle()->get_owner()->get_name() << " no longer owns " << search_for_vehicle()->get_desc() << " " << search_for_vehicle()->get_id().get_registration() << "!\n";
                    search_for_vehicle()->release_owner();

                    search_for_vehicle()->add_owner(*search_for_person());
                    std::cout << search_for_person()->get_name() << " has acquired " << search_for_vehicle()->get_desc() << " "
                              << command_specification2 << "!\n";
                }
                else
                {
                    std::cout << "This vehicle is already owned by this person!\n";
                }
            }
        }
        else
        {
            throw std::out_of_range("");
        }
    }
    catch (std::out_of_range)
    {
        std::cerr << "Aquiring falied!" << '\n';
    }
}

void Commands::do_Release()
{
    try
    {
        if (search_for_person() && search_for_vehicle())
        {
            if (search_for_person() == search_for_vehicle()->get_owner())
            {
                search_for_vehicle()->release_owner();
                std::cout << search_for_person()->get_name()
                          << " no longer owns " << search_for_vehicle()->get_desc() << " "
                          << search_for_vehicle()->get_id().get_registration() << "!\n";
            }
            else
            {
                throw std::invalid_argument("");
            }
        }
        else
        {
            throw std::out_of_range("");
        }
    }
    catch (std::invalid_argument)
    {
        std::cerr << "Person " << search_for_person()->get_name() << " does not own " << search_for_vehicle()->get_id().get_registration() << '\n';
    }
    catch (std::out_of_range)
    {
        ; // empty the other try_catch handles it
    }
}

void Commands::do_Show()
{
    try
    {
        if (command_specification1[0] != '[' || command_specification1[command_specification1.size() - 1] != ']')
        {
            throw std::invalid_argument("");
        }
    }
    catch (std::invalid_argument)
    {
        std::cerr << "Invalid command!#" << '\n';
        return;
    }

    short type_of_show = check_for_type();

    try
    {
        if (type_of_show == 1)
        {
            Person::print_all_people();
        }
        else if (type_of_show == 2)
        {
            Vehicle::print_all_vehicles();
        }
        else if (type_of_show == 3)
        {
            size_t i = 8;
            unsigned int id = 0;
            while (command_specification1[i] && i < command_specification1.size() - 1)
            {
                id += int(command_specification1[i] - '0') * int(pow(10, command_specification1.size() - (i + 2)) + EPS);
                i++;
            }

            Person::print_person(id);
        }
        else if (type_of_show == 4)
        {
            std::string v_id;
            size_t i = 10;
            while (i < command_specification1.size() - 1)
            {
                v_id.push_back(command_specification1[i]);
                i++;
            }

            Registration reg(v_id);

            Vehicle::print_vehicle(reg);
        }
        else if (type_of_show == -1)
        {
            throw std::invalid_argument("");
        }
    }
    catch (std::invalid_argument)
    {
        std::cerr << "Invalid command!" << '\n';
    }
}

void Commands::do_Remove()
{
    if (Validation::is_digit(command_specification1[0]))
    {
        size_t i = 0;
        unsigned int id = 0;
        try
        {
            id = std::stoi(command_specification1);
            Person::remove_person(id);
        }
        catch (...)
        {
            std::cerr << "An error has occured! Removing failed!" << '\n';
        }
    }
    else if (Validation::is_letter(command_specification1[0]))
    {
        Registration reg(command_specification1);

        Vehicle::remove_vehicle(reg);
    }
    else
    {
        try
        {
            throw std::invalid_argument("");
        }
        catch (std::invalid_argument)
        {
            std::cerr << "<what> can start only with a capital letter or digit!" << '\n';
        }
    }
}

void Commands::do_Save() // I have decided that it does not make sense to save the information onto a file
                         // and then to pass the same file as a command line argument therefore the txt file which
                         // is generated by this command shows in a convinient way the information from the database
{
    try
    {
        if (command_specification1[command_specification1.size() - 1] != 't' ||
            command_specification1[command_specification1.size() - 2] != 'x' ||
            command_specification1[command_specification1.size() - 3] != 't')
        {
            throw std::invalid_argument("");
        }

        std::ofstream out(command_specification1);

        out << "People:\n";

        if (out.is_open())
        {
            for (size_t i = 0; i < Person::existing_people.size(); i++)
            {
                out << "|"
                    << " " << Person::existing_people[i].get_name() << " " << Person::existing_people[i].get_id();
                if (!get_all_vehicles(&Person::existing_people[i]).empty())
                {
                    for (size_t j = 0; j < get_all_vehicles(&Person::existing_people[i]).size(); j++)
                    {
                        out << " | " << get_all_vehicles(&Person::existing_people[i])[j].get_desc() << " ";
                        out << get_all_vehicles(&Person::existing_people[i])[j].get_id().get_registration();
                    }
                }
                out << "\n";
            }
            out << "\nVehicles:\n";

            for (size_t i = 0; i < Vehicle::existing_vehicles.size(); i++)
            {
                out << "| " << Vehicle::existing_vehicles[i].get_desc() << " "
                    << Vehicle::existing_vehicles[i].get_id().get_registration();
                if (!Vehicle::existing_vehicles[i].is_free())
                {
                    out << " | " << Vehicle::existing_vehicles[i].get_owner()->get_name()
                        << " " << Vehicle::existing_vehicles[i].get_owner()->get_id();
                }
                out << "\n";
            }
        }

        out.close();
    }
    catch (std::invalid_argument)
    {
        std::cerr << "Invalid file format! Files accepted: .txt" << '\n';
    }
}

void Commands::do_Commands()
{
    std::cout << "Available commands: ";
    for (size_t i = 0; i < 9; i++)
    {
        std::cout << Commands::list_of_commands[i] << " ";
    }
    std::cout << "\n";
}

void Commands::do_End()
{
    is_running = false;
}

Person *Commands::search_for_person()
{
    size_t i = 0;
    unsigned int id = 0;
    try
    {
        id = std::stoi(command_specification1);
    }
    catch (...)
    {
        std::cerr << "An error has occured!" << '\n';
        id = 0;
    }

    for (size_t j = 0; j < Person::existing_people.size(); j++)
    {
        if (Person::existing_people[j].get_id() == id)
        {
            return &Person::existing_people[j];
        }
    }

    try
    {
        throw std::out_of_range("");
    }
    catch (std::out_of_range)
    {
        std::cerr << "Person does not exist!" << '\n';
    }

    return nullptr;
}

Vehicle *Commands::search_for_vehicle()
{
    try
    {
        for (size_t i = 0; i < Vehicle::existing_vehicles.size(); i++)
        {
            if (command_specification2 == Vehicle::existing_vehicles[i].get_id().get_registration())
            {

                return &Vehicle::existing_vehicles[i];
            }
        }

        throw 404;
    }
    catch (int)
    {
        std::cerr << "Vehicle does not exist!" << '\n';
    }
    catch (std::invalid_argument)
    {
        std::cerr << "This vehicle is not owned by this person!" << '\n';
    }

    return nullptr;
}

short Commands::check_for_type()
{
    command_specification1 = Validation::to_upper_all(command_specification1);

    if (command_specification1 == "[PEOPLE]")
    {
        return 1;
    }
    else if (command_specification1 == "[VEHICLES]")
    {
        return 2;
    }
    else if (show_person())
    {
        return 3;
    }
    else if (show_vehicle())
    {
        return 4;
    }

    return -1;
}

bool Commands::show_person() const
{
    std::string copy_com;

    for (size_t i = 0; i <= 7; i++)
    {
        copy_com.push_back(command_specification1[i]);
    }

    return copy_com == "[PEOPLE|";
}

bool Commands::show_vehicle() const
{
    std::string copy_com;

    for (size_t i = 0; i <= 9; i++)
    {
        copy_com.push_back(command_specification1[i]);
    }

    return copy_com == "[VEHICLES|";
}

void Commands::open_file(std::string file_name)
{
    try
    {
        if (file_name[file_name.size() - 1] != 't' ||
            file_name[file_name.size() - 2] != 'x' ||
            file_name[file_name.size() - 3] != 't')
        {
            throw std::invalid_argument("");
        }

        std::ifstream in(file_name);

        if (in.is_open())
        {
            while (!in.eof())
            {
                std::string temp;
                std::getline(in, temp);
                if (!in.eof())
                {
                    Commands com(temp);
                    com.do_command();
                }
            }

            in.close();
        }
        else
        {
            throw std::domain_error("");
        }
    }
    catch (std::invalid_argument)
    {
        std::cerr << "Invalid file format!" << '\n';
    }
    catch (std::domain_error)
    {
        std::cerr << "File does not exist!" << '\n'; // Program ends!
        is_running = false;
    }
}
