#pragma once

#include <iostream>  // Для ввода/вывода
#include <string>    // Для std::string
#include <iomanip>   // Для __quoted и std::setprecision
#include "../Hash/Functional.h"
#include "Extractor.h"
#include <ios>
using namespace std;

class Person {
private:
    int id;
    string firstName;
    string lastName;
    int birthYear;
    double height;
    double weight;
    
public:
    Person() : id(0), firstName(""), lastName(""), birthYear(0), height(0.0), weight(0.0) {}

    Person(int id, const string& firstName,const string& lastName, int birthYear, double height, double weight)
        : id(id), firstName(firstName), lastName(lastName), birthYear(birthYear), height(height), weight(weight) {}

    friend istream& operator>>(istream& inStream, Person& person) {
        string prefix;
        inStream >> prefix; // Считываем "PERSON:"
        if (prefix != "[PERSON:") {
            inStream.setstate(ios::failbit); // Устанавливаем ошибку, если формат не совпадает
            return inStream;
        }

        char comma; // Для пропуска запятых
        string firstName, lastName;

        if (inStream
            >> person.id            // Считываем id
            >> comma                // Пропускаем запятую
            >> __quoted(firstName)     // Считываем FirstName в кавычках
            >> comma                // Пропускаем запятую
            >> __quoted(lastName)     // Считываем LastName в кавычках
            >> comma                // Пропускаем запятую
            >> person.birthYear     // Считываем год рождения
            >> comma                // Пропускаем запятую
            >> person.height        // Считываем рост
            >> comma                // Пропускаем запятую
            >> person.weight) {     // Считываем вес
            person.firstName = firstName;
            person.lastName = lastName;
            } else {
                inStream.setstate(ios::failbit); // Если произошла ошибка при чтении
            }

        return inStream;
    }

    friend std::ostream& operator<<(std::ostream& outStream, const Person& person) {
        outStream << "(PERSON: "
           << person.id << " , "
           << __quoted(person.firstName) << " , "
           << __quoted(person.lastName) << " , "
           << person.birthYear << " , "
           << fixed << setprecision(2) << person.height << " , "
           << fixed << setprecision(2) << person.weight << ")";
        return outStream;
    }
    
    int GetID() const {return this->id;}
    string GetFirstName() const {return this->firstName;}
    string GetLastName() const {return this->lastName;}
    int GetBirthYear() const {return this->birthYear;}
    double GetHeight() const {return this->height;}
    double GetWeight() const {return this->weight;}
    
    bool operator==(const Person& other){
        return (this->firstName == other.GetFirstName() &&
                this->lastName == other.GetLastName() &&
                this->birthYear == other.GetBirthYear() &&
                this->height == other.GetHeight() &&
                this->weight == other.GetWeight() &&
                this->id == other.GetID());
    }
    
    void generation()
    {
        birthYear = 1900 + rand() % 101;
        weight = rand() % 150 + 20;
        height = 150 + rand() % 50;
        firstName.resize(10);
        for (int i = 0; i < 10; ++i)
        {
            firstName[i] = rand() % 25 + 97;
        }
        lastName = firstName;
    }
};

inline bool AscendingInt(const int& first, const int& second) {return first < second;}

inline bool DescendingInt(const int& first, const int& second) {return first > second;}

inline bool CompareFirstName(const Person& a, const Person& b) {return a.GetFirstName() < b.GetFirstName();}

inline bool CompareLastName(const Person& a, const Person& b) {return a.GetLastName() < b.GetLastName();}

inline bool CompareId(const Person& a, const Person& b) {return a.GetID() > b.GetID();}
inline bool CompareBirthYear(const Person& a, const Person& b) {return a.GetBirthYear() > b.GetBirthYear();}

inline bool CompareHeight(const Person& a, const Person& b) {return a.GetHeight() < b.GetHeight();}

//Хеш-функция для Person
namespace chf{
    inline int hash(const Person& person, unsigned int capacity){
        return hash(person.GetID() + person.GetBirthYear() + hash(person.GetFirstName(), capacity) + hash(person.GetLastName(), capacity), capacity);
    }

    inline bool isEqual(const Person& x, const Person& y){
        return (x.GetFirstName() == y.GetFirstName() &&
                x.GetLastName() == y.GetLastName() &&
                x.GetBirthYear() == y.GetBirthYear() &&
                x.GetHeight() == y.GetHeight() &&
                x.GetWeight() == y.GetWeight() &&
                x.GetID() == y.GetID());
    }
}
