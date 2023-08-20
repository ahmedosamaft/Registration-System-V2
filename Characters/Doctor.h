//
// Created by andro on 8/18/2023.
//

#ifndef REGISTRATION_SYSTEM_V2_DOCTOR_H
#define REGISTRATION_SYSTEM_V2_DOCTOR_H
#include "../Material/Course.h"
#include "Person.h"
#include <memory>
#include <vector>

namespace Faculty {

    class Doctor: public Person{
    private:
        std::vector<std::shared_ptr<Material::Course>> teaching_course;

    public:
        Doctor();
        explicit Doctor(string &);
        Doctor(const string &, const string &, const string &, long long);

    public:
        const string ToString() override;
        const std::vector<std::shared_ptr<Material::Course>> getTeachingCourse() const;
        void setTeachingCourse(const std::vector<std::shared_ptr<Material::Course>> &teachingCourse);
        void addCourse(std::shared_ptr<Material::Course> &teachingCourse);
    };

}// namespace Faculty

#endif//REGISTRATION_SYSTEM_V2_DOCTOR_H
