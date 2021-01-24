#include "Accident.hpp"

Accident::Accident(Date date, string description) {
    this->date = date;
    this->description = description;
}

Accident::Accident() {
}

Date Accident::getDate() {
    return this->date;
}

void Accident::setDate(Date date) {
    this->date = date;
}

string Accident::getDescription() {
    return this->description;
}

void Accident::setDescription(string description) {
    this->description = description;
}