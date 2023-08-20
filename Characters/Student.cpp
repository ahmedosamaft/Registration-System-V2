//
// Created by andro on 8/18/2023.
//

#include "Student.h"
#include "../Helper.h"
#include "../Mangers/StudentManger.h"

namespace Faculty {

    Student::Student() : Person() {}
    Student::Student(const string &userName, const string &password, const string &name, long long id) : Person(userName, password, name, id) {}
    Student::Student(string &Line) {
        std::vector<std::string> parse = Helper::parseLine(Line, ',');
        this->user_name = parse[1];
        this->password = parse[2];
        this->name = parse[3];
        this->id = std::stoll(parse[0]);
    }

    const string Student::ToString() {
        std::vector<string> ent;
        ent.push_back(std::to_string(this->id));
        ent.push_back(this->user_name);
        ent.push_back(this->password);
        ent.push_back(this->name);
        return Helper::makeEntity(ent, ',');
    }

    const std::vector<std::shared_ptr<Material::Course>>& Student::getRegisteredCourse() const {
        return registered_course;
    }

    void Student::addCourse(std::shared_ptr<Material::Course> &registeredCourse) {
        registered_course.push_back(registeredCourse);
    }

    void Student::setRegisteredCourse(const std::vector<std::shared_ptr<Material::Course>> &registeredCourse) {
        registered_course = registeredCourse;
    }
    const std::vector<std::shared_ptr<Material::AssignmentSolution>> &Student::getSolutions() const {
        return solutions;
    }
    void Student::addSolution(std::shared_ptr<Material::AssignmentSolution> &solution) {
        Student::solutions.push_back(solution);
    }
}// namespace Faculty