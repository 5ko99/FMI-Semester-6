#pragma once
#include<iostream>
class PictureData {
private:
    char* f_description;
    unsigned f_likesCount;
    unsigned f_commentsCount;
public:
    PictureData(const char *description = "", unsigned likes = 0, unsigned comments = 0);
    PictureData(const PictureData& other);
    PictureData& operator=(const PictureData& other);
    ~PictureData();
    void setDescription(const char* newDescription);
    friend std::ofstream& operator<<(std::ofstream& out, const PictureData& data);
    friend std::ifstream& operator>>(std::ifstream& in, PictureData& data);

private:
    void copy(const PictureData& other);
    void del();
};


