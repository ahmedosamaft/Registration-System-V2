//
// Created by andro on 8/18/2023.
//

#include "Doctor.h"
#include "../Helper.h"

namespace Faculty {

    Doctor::Doctor() : Person() {}
    Doctor::Doctor(string &Line) {
        std::vector<std::string> parse = Helper::parseLine(Line, ',');
        this->user_name = parse[1];
        this->password = parse[2];
        this->name = parse[3];
        this->id = std::stoll(parse[0]);
    }
    Doctor::Doctor(const string &userName, const string &password,const string& name, long long id) : Person(userName, password,name, id) {}

    const string Doctor::ToString() {
        std::vector<string> ent;
        ent.push_back(std::to_string(this->id));
        ent.push_back(this->user_name);
        ent.push_back(this->password);
        ent.push_back(this->name);
        return Helper::makeEntity(ent,',');
    }

    const std::vector<std::shared_ptr<Material::Course>> Doctor::getTeachingCourse() const {
        return teaching_course;
    }

    void Doctor::setTeachingCourse(const std::vector<std::shared_ptr<Material::Course>> &teachingCourse) {
        teaching_course = teachingCourse;
    }

    void Doctor::addCourse(std::shared_ptr<Material::Course> &teachingCourse) {
        teaching_course.push_back(teachingCourse);
    }
}// namespace Faculty