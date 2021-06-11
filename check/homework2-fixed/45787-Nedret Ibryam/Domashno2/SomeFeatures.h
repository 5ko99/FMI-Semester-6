#ifndef SOMEFEATURES_H_INCLUDED
#define SOMEFEATURES_H_INCLUDED

int strsize(const char *str)
{
    int i=0;
    while(*str)
    {
        i++;
        str++;
    }
    return i;
}

void strcpy_safemode(char *p1, const char *p2, int sz)
{
    int i;
    //std::cout<<"=>"<<sizeof(p1)/sizeof(p1[0])<<std::endl;
    //std::cout<<"=>"<<sizeof(p2)/sizeof(p1[0])<<std::endl;

    /*if(sz>strsize(p2))
    {
        std::cout<<"The length of the argument(char array) is less than the specified size\n";
        return;
    }*/

    for(i=0; i<sz; i++)
    {
        *p1++=*p2++;
    }
    *p1='\0';
}

std::string convertToString(const char *str, int sz)
{
    std::string s="";
    int i;
    for(i=0; i<sz; i++)
    {
        s+=*str++;
    }
    return s;
}

bool correctID(const char *id)
{
    int sz=strsize(id), i;
    if(sz==0) return false;
    for(i=0; i<sz; i++)
    {
        if(*(id+i)>='A'&&*(id+i)<='Z') return false;
        if(*(id+i)>='a'&&*(id+i)<='z') return false;
    }
    return true;
}

int cmp_commands(const char *p1, const char *p2)
{
    unsigned int sizep1=strlen(p1), sizep2=strlen(p2);
    if(sizep1!=sizep2) return 1;

    while(*p1)
    {
        if(tolower(*p1)!=(*p2)) return 1;
        p1++;
        p2++;
    }
    return 0;
}

#endif // SOMEFEATURES_H_INCLUDED
