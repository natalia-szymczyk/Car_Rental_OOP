#pragma once 

#ifndef Accident_hpp
#define Accident_hpp

#include "Date.hpp"

class Accident{
    protected:
        Date date;
        string description;

    public:
        Accident();
        Accident(Date date, string description);
        Date getDate();
        void setDate(Date date);
        string getDescription();
        void setDescription(string description);


};

#endif