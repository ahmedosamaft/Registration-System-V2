//
// Created by andro on 8/18/2023.
//

#ifndef REGISTRATION_SYSTEM_V2_STUDENT_H
#define REGISTRATION_SYSTEM_V2_STUDENT_H
#include "../Material/AssignmentSolution.h"
#include "../Material/Course.h"
#include "Person.h"
#include <memory>
#include <vector>

namespace Faculty {

    class Student : public Person {
    private:
        std::vector<std::shared_ptr<Material::Course>> registered_course;
        std::vector<std::shared_ptr<Material::AssignmentSolution>> solutions;

    public:
        Student();
        explicit Student(string &);
        Student(const string &, const string &, const string &, long long);

    public:
        const string ToString() override;
        const std::vector<std::shared_ptr<Material::Course>>& getRegisteredCourse() const;
        void setRegisteredCourse(const std::vector<std::shared_ptr<Material::Course>> &registeredCourse);
        void addCourse(std::shared_ptr<Material::Course> &registeredCourse);
        const std::vector<std::shared_ptr<Material::AssignmentSolution>> &getSolutions() const;
        void addSolution(std::shared_ptr<Material::AssignmentSolution> &solution);
    };

}// namespace Faculty

#endif//REGISTRATION_SYSTEM_V2_STUDENT_H
