//
// Created by andro on 8/18/2023.
//

#include "Person.h"
#include <utility>

const string &Person::getUserName() const {
    return user_name;
}

void Person::setUserName(const string &userName) {
    user_name = userName;
}

Person::Person(string userName, string password, string name, long long id) : user_name(std::move(userName)), name(std::move(name)), password(std::move(password)), id(id) {}
Person::Person() {}
Person::Person(const string &Line) {}

const string &Person::getPassword() const {
    return password;
}

const string &Person::getName() const {
    return name;
}

void Person::setPassword(const string &Password) {
    password = Password;
}

void Person::setName(const string &Name) {
    name = Name;
}

bool Person::equals(string &userName, string &Password) {
    return (this->user_name == userName && this->password == Password);
}

const string Person::ToString() {
    return std::string();
}
long long int Person::getId() const {
    return id;
}
void Person::setId(long long int id) {
    Person::id = id;
}
