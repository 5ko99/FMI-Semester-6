#ifndef COMMANDS_H_INCLUDED
#define COMMANDS_H_INCLUDED

void console()
{
    char str[1000];
    char nextcommand[30][100];
    unsigned short int i, j, k, sz=0, p, z, space;
    bool proend=false, same, same2;

    Vehicle mps;
    Person ppl;
    Registration rgs;

    std::vector<Person> per_vec;
    std::vector<Vehicle> veh_vec;

    do{
        std::cout<<"> ";
        gets(str);
        sz=strlen(str);

        j=0, p=0, k=0, space=0, z=0;

        for(i=0; i<sz; i++)
        {
            if(str[i]!=' ')
            {
                p=i;
                break;
            }
        }

        for(i=p; i<sz; i++) // Р’Р—Р•РњРђРњР• Р’РЎРР§РљР Р”РЈРњР РћРў РЎРўР РРќР“Рђ (РљРћРњРђРќР”РРўР•)
        {
            if(str[i]=='\"')
            {
                nextcommand[k][j]='\0';
                if(strsize(nextcommand[k])!=0) k++;
                j=0;
                for(z=i+1; z<sz; z++)
                {
                    if(str[z]=='\"') break;
                    nextcommand[k][j]=str[z];
                    j++;
                }
                i=z;
            }
            else
            {

                if(str[i]==' ') space++;
                else if(str[i]!=' '&&i!=sz)
                {
                    if(space>0)
                    {
                        nextcommand[k][j]='\0';
                        k++;
                        j=0;
                        space=0;
                    }
                    nextcommand[k][j]=str[i];
                    j++;
                }
            }
        }
        nextcommand[k][j]='\0'; // РљР РђР™ РќРђ РђР›Р“РћР РРўРЄРњРђ Р—Рђ Р’Р—Р•РњРђРќР• РќРђ РљРћРњРђРќР”РРўР•

        //for(i=0; i<=k; i++)
        //{
        //    std::cout<<i<<' '<<nextcommand[i]<<std::endl;
        //}


        same=false, same2=false;
        if(!cmp_commands(nextcommand[0], "vehicle"))
        {
            // VEHICLE <registration> <description>
            if(!is_valid(nextcommand[1]))
            {
                std::cout<<"Wrong registration number!"<<std::endl;
                std::cout<<"Example: XXYYYYXX OR XYYYYXX | X is a letter between A and Z / Y is a digit between 0 and 9"<<std::endl;
            }
            else
            {
                // РџР РћР’Р•Р РљРђ Р”РђР›Р РРњРђ Р•Р”РќРђРљР’Р Р Р•Р“РРЎРўР РђР¦РРћРќРќР РќРћРњР•Р Рђ
                sz=veh_vec.size();
                for(i=0; i<sz; i++)
                {
                    if(!strcmp(veh_vec[i].getVehicleRegistration(), nextcommand[1]))
                    {
                        std::cout<<"There is a vehicle with such a registration number!"<<std::endl;
                        same=true;
                    }
                }
                if(same==false)
                {
                    mps.setVehicleRegistration(nextcommand[1]);
                    if(k>=2) mps.setVehicleDescription(nextcommand[2]);
                    veh_vec.push_back(mps);
                }
            }
        }
        if(!cmp_commands(nextcommand[0], "person"))
        {
            // PERSON <name> <id>
            if(k<2) // РџР РћР’Р•Р РљРђ РќРђ Р‘Р РћРЇ РђР Р“РЈРњР•РќРўР РџРћР”РђР”Р•РќР РќРђ РљРћР—РћР›РђРўРђ
            {
                std::cout<<"Usage: PERSON <name> <id>"<<std::endl;
            }
            else
            {
                if(correctID(nextcommand[2])==false) // AKO K>2 РџР РћР’Р•Р РЇР’РђРњР• Р—Рђ Р’РђР›РР”Р•Рќ ID РђР”Р Р•РЎ
                {
                    std::cout<<"Wrong ID!"<<std::endl;
                }
                else
                {
                    // РџР РћР’Р•Р РљРђ Р”РђР›Р РРњРђ Р•Р”РќРђРљР’Р ID
                    int id=atoi(nextcommand[2]);

                    sz=per_vec.size();
                    for(i=0; i<sz; i++)
                    {
                        if(per_vec[i].getID()==id)
                        {
                            std::cout<<"There is a person with such an ID card!"<<std::endl;
                            same=true;
                        }
                    }

                    // РђРљРћ РќРЇРњРђ Р•Р”РќРђРљР’Р ID РЎР• Р”РћР‘РђР’РЇ
                    if(same==false)
                    {
                        ppl.setName(nextcommand[1]);
                        ppl.setID(id);
                        per_vec.push_back(ppl);
                    }
                }
            }
        }
        if(!cmp_commands(nextcommand[0], "acquire"))
        {
            // ACQUIRE <owner-id> <vehicle-id>
            // Р—РђР”РЄР›Р–РРўР•Р›РќРћ РўР РЇР‘Р’Рђ Р”Рђ РРњРђ РЎРЄРЁР•РЎРўР’РЈР’РђР© OWNER Р VEHICLE Р’ РџР РћРўРР’Р•Рќ РЎР›РЈР§РђР™ РќРЇРњРђ Р”Рђ РЎР• РР—РџРЄР›РќР РљРћРњРђРќР”РђРўРђ

            if(k<2) // РџР РћР’Р•Р РљРђ РќРђ Р‘Р РћРЇ РђР Р“РЈРњР•РќРўР РџРћР”РђР”Р•РќР РќРђ РљРћР—РћР›РђРўРђ
            {
                std::cout<<"Usage: ACQUIRE <owner-id> <vehicle-id>"<<std::endl;
            }
            else
            {
                if(correctID(nextcommand[1])==false) // AKO K>2 РџР РћР’Р•Р РЇР’РђРњР• Р—Рђ Р’РђР›РР”Р•Рќ ID РђР”Р Р•РЎ
                {
                    std::cout<<"Wrong ID!"<<std::endl;
                }
                else if(!is_valid(nextcommand[2])) // РџР РћР’Р•Р РљРђ Р—Рђ Р’РђР›РР”Р•Рќ РќРћРњР•Р 
                {
                    std::cout<<"Wrong registration number!"<<std::endl;
                    std::cout<<"Example: XXYYYYXX OR XYYYYXX | X is a letter between A and Z / Y is a digit between 0 and 9"<<std::endl;
                }
                else
                {
                    int cnt=0, save_pos1=0, save_pos2=0;
                    sz=per_vec.size();
                    for(i=0; i<sz; i++) // РќРђРњРР РђРњР• Р§РћР’Р•Рљ РЎ Р”РђР”Р•РќРћРўРћ ID (Р”РђР›Р РЎРЄРЁР•РЎРўР’РЈР’Рђ)
                    {
                        if(per_vec[i].getID()==atoi(nextcommand[1]))
                        {
                            save_pos1=i;
                            same=true;
                            break;
                        }
                        cnt++;
                    }

                    sz=veh_vec.size();
                    for(i=0; i<sz; i++) // РќРђРњРР РђРњР• РџР Р•Р’РћР—РќРћРўРћ РЎР Р•Р”РЎРўР’Рћ РЎ Р”РђР”Р•РќРРЇ РќР Р Р•Р“РРЎРўР РђР¦РРћРќР•Рќ РќРћРњР•Р  (Р”РђР›Р РЎРЄР©Р•РЎРўР’РЈР’Рђ)
                    {
                        if(!strcmp(veh_vec[i].getVehicleRegistration(), nextcommand[2]))
                        {
                            save_pos2=i;
                            same2=true;
                            break;
                        }
                    }

                    if(same==false) // РђРљРћ РќР• Р• РќРђРњР•Р Р•Рќ Р§РћР’Р•Рљ Р Р”РђР”Р•РќРћРўРћ ID РР—Р’Р•Р–Р”Рђ РЎРЄРћР‘Р©Р•РќРР• Р—Рђ Р“Р Р•РЁРљРђ Р РќР• РџР РђР’Р РќРР©Рћ
                    {
                        std::cout<<"There is no person with such an id!"<<std::endl;
                    }
                    if(same2==false) // РђРљРћ РќР• Р• РќРђРњР•Р Р•РќРћ РџР Р•Р’РћР—РќРћ РЎР Р•Р”РЎРўР’Рћ РЎРЄРЎ Р—РђР”РђР”Р•РќРРЇ Р Р•Р“РРЎРўР РђР¦РРћРќР•Рќ РќРћРњР•Р  РР—Р’Р•Р–Р”Рђ РЎРЄРћР‘Р©Р•РќРР• Р—Рђ Р“Р Р•РЁРљРђ Р РќР• РџР РђР’Р РќРР©Рћ
                    {
                        std::cout<<"There is no vehicle with such a registration number!"<<std::endl;
                    }
                    if(same==true&&same2==true) // РђРљРћ РЎРЄРЁР•РЎРўР’РЈР’РђРў Р Р”Р’Р•РўР• (PERSON AND VEHICLE) РЎР• РР—РџРЄР›РќРЇР’Рђ РљРћРњРђРќР”РђРўРђ
                    {
                        sz=per_vec.size();
                        for(i=0; i<sz; i++) // РўРЄР РЎРРњ Р§РћР’Р•Рљ РљРћР™РўРћ РџР РРўР•Р–РђР’Рђ РЎРЄРћРўР’Р•РўРќРћРўРћ РџР Р•Р’РћР—РќРћ РЎР Р•Р”РЎРўР’Рћ Р РЎР• РџР Р•РњРђРҐР’Рђ РЎРћР‘РЎРўР’Р•РќРћРЎРўРўРђ
                        {
                            per_vec[i].removeVehicle(nextcommand[2]);
                        }

                        per_vec[save_pos1].addNewRegNumber(nextcommand[2]);
                        veh_vec[save_pos2].setOwner(&per_vec.at(cnt));
                    }
                }
            }
        }
        if(!cmp_commands(nextcommand[0], "release"))
        {
            // RELEASE <owner-id> <vehicle-id>
            if(k<2) // РџР РћР’Р•Р РљРђ РќРђ Р‘Р РћРЇ РђР Р“РЈРњР•РќРўР РџРћР”РђР”Р•РќР РќРђ РљРћР—РћР›РђРўРђ
            {
                std::cout<<"Usage: RELEASE <owner-id> <vehicle-id>"<<std::endl;
            }
            else
            {
                if(correctID(nextcommand[1])==false) // AKO K>2 РџР РћР’Р•Р РЇР’РђРњР• Р—Рђ Р’РђР›РР”Р•Рќ ID РђР”Р Р•РЎ
                {
                    std::cout<<"Wrong ID!"<<std::endl;
                }
                else if(!is_valid(nextcommand[2])) // РџР РћР’Р•Р РљРђ Р—Рђ Р’РЄР’Р•Р”Р•Рќ Р’РђР›РР”Р•Рќ Р Р•Р“РРЎРўР РђР¦РРћРќР•Рќ РќРћРњР•Р 
                {
                    std::cout<<"Wrong registration number!"<<std::endl;
                    std::cout<<"Example: XXYYYYXX OR XYYYYXX | X is a letter between A and Z / Y is a digit between 0 and 9"<<std::endl;
                }
                else
                {
                    bool is_deleted=false;
                    sz=per_vec.size();
                    for(i=0; i<sz; i++) // РўРЄР РЎР•РќР• РќРђ PERSON
                    {
                        if(per_vec[i].getID()==atoi(nextcommand[1])) // РђРљРћ Р• РќРђРњР•Р Р•Рќ PERSON РЎРЄРЎ Р—РђР”РђР”Р•РќРћРўРћ ID РЎР• РР—РўР РР’Рђ Р Р•Р“РРЎРўР РђР¦РРћРќРќРРЇ РќРћРњР•Р 
                        {
                            is_deleted=per_vec[i].removeVehicle(nextcommand[2]); // TRUE - Р—РќРђР§Р Р• Р‘РР›Рћ РџР Р•РњРђРҐРќРђРўРћ РџР Р•Р’РћР—РќРћ РЎР Р•Р”РЎРўР’Рћ
                            same=true;
                            break;
                        }
                    }

                    if(same==false)
                    {
                        std::cout<<"There is no person with such an id!"<<std::endl;
                    }
                    else if(is_deleted==true)
                    {
                        sz=veh_vec.size();
                        for(i=0; i<veh_vec.size(); i++) // РќРђРњРР Рђ РџР Р•Р’РћР—РќРћРўРћ РЎР Р•Р”РЎРўР’Рћ РЎ Р”РђР”Р•РќРРЇ Р Р•Р“РРЎРўР РђР¦РРћРќР•Рќ РќРћРњР•Р  Р РџР Р•РњРђРҐР’Рђ РЎРћР‘РЎРўР’Р•РќРРљРђ (РћРЎРўРђР’Рђ Р‘Р•Р— РЎРћР‘РЎРўР’Р•РќРРљ)
                        {
                            if(!strcmp(veh_vec[i].getVehicleRegistration(), nextcommand[2]))
                            {
                                veh_vec[i].setOwner(nullptr);
                                break;
                            }
                        }
                    }
                }
            }
        }
        if(!cmp_commands(nextcommand[0], "remove"))
        {
            // REMOVE <what>
            if(k<1)
            {
                std::cout<<"Usage: <what> / <what> is id per person or car registration number (must exist)"<<std::endl;
            }
            else
            {
                if(is_valid(nextcommand[1]))
                {
                    sz=veh_vec.size();
                    for(i=0; i<sz; i++) // РўРЄР РЎРРњ РћР‘Р•РљРў РЎ Р”РђР”Р•Рќ Р Р•Р“РРЎРўР РђР¦РРћРќР•Рќ РќРћРњР•Р 
                    {
                        if(!strcmp(veh_vec[i].getVehicleRegistration(), nextcommand[1])) // РђРљРћ Р• РќРђРњР•Р Р•РќРћ
                        {
                            char c;
                            std::cout<<"Do you want to delete a vehicle with registration number - "<<nextcommand[1]<<"? (Y/N)? ";
                            std::cin>>c;
                            if(toupper(c)=='Y')
                            {
                                int sz2=per_vec.size();
                                for(j=0; j<sz2; j++)
                                {
                                    per_vec[i].removeVehicle(nextcommand[1]); // РЎРћР‘РЎРўР’Р•РќРРљРђ Р’Р•Р§Р• РќР• Р“Рћ РџР РРўР•Р–РђР’Рђ
                                }
                                veh_vec[i].setOwner(nullptr);
                                ///std::swap(veh_vec[i], veh_vec[sz-1]);
                                ///veh_vec.pop_back();
                                //veh_vec.erase(veh_vec.begin()+i); // РџР Р•РњРђРҐР’РђРњР• Р“Рћ РћРў Р’Р•РљРўРћР Рђ
                            }
                            same=true;
                            break;
                        }
                    }
                    if(same==false) // РђРљРћ РќРЇРњРђ РўРђРљРЄР’ РћР‘Р•РљРў РР—Р’Р•Р–Р”РђРњР• РЎРЄРћР‘Р©Р•РќРР• Р—Рђ Р“Р Р•РЁРљРђ
                    {
                        std::cout<<"The vehicle with registration number "<<nextcommand[1]<<" does not exist!"<<std::endl;
                    }
                }
                else if(correctID(nextcommand[1])==true)
                {
                    sz=per_vec.size();
                    for(i=0; i<sz; i++)
                    {
                        if(per_vec[i].getID()==atoi(nextcommand[1]))
                        {
                            int sz2=veh_vec.size();
                            for(j=0; j<sz2; j++)
                            {
                                if(per_vec[i].getID()==veh_vec[j].getOwnerID())
                                {
                                    veh_vec[j].setOwner(nullptr);
                                }
                            }
                            per_vec.erase(per_vec.begin()+i);
                            same=true;
                            break;
                        }
                    }
                    if(same==false)
                    {
                        std::cout<<"A person with id "<<nextcommand[1]<<" does not exist!"<<std::endl;
                    }
                }
                else
                {
                    std::cout<<"Wrong ID or registration number!"<<std::endl;
                }
            }
        }
        if(!cmp_commands(nextcommand[0], "save"))
        {
            // SAVE <path>
        }
        if(!cmp_commands(nextcommand[0], "show"))
        {
            //SHOW [PEOPLE|VEHICLES|<id>] <id> - РњРћР–Р• Р”Рђ Р• ID РќРђ PERSON РР›Р Р Р•Р“РРЎРўР РђР¦РРћРќР•Рќ РќРћРњР•Р 
            if(k<1) // РџР РћР’Р•Р РљРђ РќРђ РџРћР”РђР”Р•РќРРЇ Р‘Р РћР™ РђР Р“РЈРњР•РќРўР
            {
                std::cout<<"Usage: SHOW [PEOPLE|VEHICLES|<id>]"<<std::endl;
            }
            else
            {
                if(!cmp_commands(nextcommand[1], "people"))
                {

                    if(k==1) // РђРљРћ Р• РЎРђРњРћ "PEOPLE" РЎР• РР—Р’Р•Р–Р”Рђ РљР РђРўРљРђРўРђ РРќР¤РћР РњРђР¦РРЇ
                    {
                        sz=per_vec.size();
                        for(i=0; i<sz; i++)
                        {
                            per_vec[i].printPersonSmallInfo();
                            std::cout<<"\n";
                        }
                    }
                    else
                    {
                        if(correctID(nextcommand[2])==false) // РџР РћР’Р•Р РЇР’РђРњР• Р—Рђ Р’РђР›РР”Р•Рќ ID РђР”Р Р•РЎ
                        {
                            std::cout<<"Wrong ID!"<<std::endl;
                        }
                        else
                        {
                            sz=per_vec.size(); // РўРЄР РЎРРњ Р—РђР”РђР”Р•РќРРЇ ID РђР”Р Р•РЎ Р РџР РРќРўРР РђРњР• РРќР¤РћР РњРђР¦РРЇРўРђ РђРљРћ Р‘РЄР”Р• РќРђРњР•Р Р•Рќ РђР”Р Р•РЎРђ
                            for(i=0; i<sz; i++)
                            {
                                if(per_vec[i].getID()==atoi(nextcommand[2]))
                                {
                                    per_vec[i].printPerson();
                                    same=true;
                                    break;
                                }
                            }

                            if(same==false)
                            {
                                std::cout<<"There is no person with such an id!"<<std::endl;
                            }
                        }
                    }
                }
                else if(!cmp_commands(nextcommand[1], "vehicles"))
                {
                    if(k==1) // РђРљРћ Р• РЎРђРњРћ "VEHICLES" РЎР• РР—Р’Р•Р–Р”Рђ РљР РђРўРљРђРўРђ РРќР¤РћР РњРђР¦РРЇ
                    {
                        sz=veh_vec.size();
                        for(i=0; i<sz; i++)
                        {
                            veh_vec[i].printVehicleSmallInfo();
                            std::cout<<"\n";
                        }
                    }
                    else
                    {
                        if(!is_valid(nextcommand[2])) // РџР РћР’Р•Р РЇР’РђРњР• Р—Рђ Р’РђР›РР”Р•Рќ Р Р•Р“РРЎРўР РђР¦РРћРќР•Рќ РќРћРњР•Р 
                        {
                            std::cout<<"Wrong registration number!"<<std::endl;
                        }
                        else
                        {
                            sz=veh_vec.size(); // РўРЄР РЎРРњ Р—РђР”РђР”Р•РќРћРўРћ РџР Р•Р’РћР—РќРћ РЎР Р•Р”РЎРўР’Рћ Р РџР РРќРўРР РђРњР• РРќР¤РћР РњРђР¦РРЇРўРђ РђРљРћ Р“Рћ РќРђРњР•Р РРњ
                            for(i=0; i<sz; i++)
                            {
                                if(!strcmp(veh_vec[i].getVehicleRegistration(), nextcommand[2]))
                                {
                                    veh_vec[i].printVehicle();
                                    same=true;
                                    break;
                                }
                            }

                            if(same==false)
                            {
                                std::cout<<"There is no vehicle with such a registration number!"<<std::endl;
                            }
                        }
                    }
                }
                else
                {
                    std::cout<<"Usage: SHOW [PEOPLE|VEHICLES|<id>]"<<std::endl;
                }
            }
        }
        if(!cmp_commands(nextcommand[0], "exit")) // РР—РҐРћР” РћРў РљРћРќР—РћР›Р•Рќ Р Р•Р–РРњ
        {
            proend=true;
            std::cout<<"Exiting the program..."<<std::endl;
        }
        if(!cmp_commands(nextcommand[0], "help")) // РџР РРќРўРР Рђ РљРћРњРђРќР”РРўР•
        {
            std::cout<<"VEHICLE <registration> <description> - Adds a vehicle."<<std::endl;
            std::cout<<"PERSON <name> <id> - Adds a person."<<std::endl;
            std::cout<<"ACQUIRE <owner-id> <vehicle-id> - Sets the new owner of the vehicle."<<std::endl;
            std::cout<<"RELEASE <owner-id> <vehicle-id> - Removal of the owner of the vehicle."<<std::endl;
            std::cout<<"REMOVE <what> - Deletes a person or vehicle."<<std::endl;
            std::cout<<"SAVE <path> - "<<std::endl;
            std::cout<<"SHOW [PEOPLE|VEHICLES|<id>] - Prints data information."<<std::endl;
            std::cout<<"EXIT - Р•xit from console mode."<<std::endl;
        }


        sz=per_vec.size();
        if(sz!=0)
        {
            std::cout<<"\n";
            std::cout<<"============================"<<std::endl;
        }
        for(i=0; i<sz; i++)
        {
            per_vec[i].printPerson();
            std::cout<<"============================"<<std::endl;
        }
        sz=veh_vec.size();
        for(i=0; i<sz; i++)
        {
            veh_vec[i].printVehicle();
            std::cout<<"============================"<<std::endl;
        }
        if(sz!=0) std::cout<<"\n";


        i=j=0;
        k=0;
    }while(proend!=true);
}

#endif // COMMANDS_H_INCLUDED
