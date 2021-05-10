#include "PictureData.h"
#include<cstring>
PictureData::PictureData(const char *description, unsigned int likes, unsigned int comments) : f_likesCount(likes),
                                                                                               f_commentsCount(
                                                                                                       comments) {
    f_description = new char[strlen(description) + 1];
    strcpy(f_description, description);
}

void PictureData::copy(const PictureData &other) {
    f_description = new char[strlen(other.f_description) + 1];

    strcpy(f_description, other.f_description);
    f_likesCount = other.f_likesCount;
    f_commentsCount = other.f_commentsCount;
}