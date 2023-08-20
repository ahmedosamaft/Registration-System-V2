//
// Created by andro on 8/18/2023.
//

#ifndef REGISTRATION_SYSTEM_V2_COURSE_H
#define REGISTRATION_SYSTEM_V2_COURSE_H
#include <memory>
#include <string>
#include <vector>
namespace Faculty {
    class Student;
    class Doctor;
}// namespace Faculty

namespace Material {
    class Assignment;

    class Course {
    private:
        std::shared_ptr<Faculty::Doctor> doctor;
        std::vector<std::shared_ptr<Faculty::Student>> students_vec;
        std::vector<std::shared_ptr<Assignment>> assignments_vec;
        std::string courseID;
        std::string name;

    public:
        Course(const std::string &courseId, const std::string &name);
        explicit Course(std::string &Line);
        Course();

    public:
        std::shared_ptr<Faculty::Doctor> &getDoctor();
        void setDoctor(const std::shared_ptr<Faculty::Doctor> &doctor);
        const std::vector<std::shared_ptr<Faculty::Student>> &getStudentsVec() const;
        void setStudentsVec(const std::vector<std::shared_ptr<Faculty::Student>> &studentsVec);
        void addStudent(std::shared_ptr<Faculty::Student> &student);
        std::pair<double,int> getGradesForStudent(std::shared_ptr<Faculty::Student> &student);
        const std::vector<std::shared_ptr<Assignment>> &getAssignmentsVec() const;
        void addAssignment(std::shared_ptr<Material::Assignment> &assignment);
        const std::string &getCourseId() const;
        void setCourseId(const std::string &courseId);
        const std::string &getName() const;
        void setName(const std::string &Name);
        std::string ToString();
        bool operator ==(std::shared_ptr<Course>);

    };

}// namespace Material

#endif//REGISTRATION_SYSTEM_V2_COURSE_H
