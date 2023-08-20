//
// Created by andro on 8/18/2023.
//

#ifndef REGISTRATION_SYSTEM_V2_PERSON_H
#define REGISTRATION_SYSTEM_V2_PERSON_H


#include <string>
using std::string;
class Person {
protected:
    long long id;
    string name;
    string password;
    string user_name;

public:
    const string &getUserName() const;
    const string &getPassword() const;
    const string &getName() const;
    long long int getId() const;
    void setId(long long int id);
    virtual const string ToString();
    bool equals(string& userName,string& Password);
    void setUserName(const string &userName);
    void setName(const string &Name);
    void setPassword(const string &Password);

public:
    Person();
    Person(string ,string ,string ,long long);
    explicit Person(const string &);
};


#endif//REGISTRATION_SYSTEM_V2_PERSON_H
