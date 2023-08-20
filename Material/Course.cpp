//
// Created by andro on 8/18/2023.
//

#include "Course.h"
#include "Assignment.h"
#include "../Characters/Doctor.h"
#include "../Mangers/StudentManger.h"
#include "../Mangers/DoctorManger.h"
#include "../Helper.h"

namespace Material {

    Course::Course(const std::string &courseId, const std::string &name) : courseID(courseId), name(name) {}
    Course::Course() {}
    // DO NOT USE THIS CONSTRUCTOR BEFORE READING DOCTORS & STUDENTS !!
    Course::Course(string &Line) {
        std::vector<std::string> parsed = Helper::parseLine(Line,',');
        this->courseID = parsed[0];
        this->name = parsed[2];
        std::shared_ptr<Course> cur {this};
        // After Reading Doctors & Students
        for (int i = 3; i < parsed.size(); ++i) {
            std::shared_ptr<Faculty::Student> &student = Mangers::StudentManger::id_student_map[std::stoll(parsed[i])];
            this->addStudent(student);
            student->addCourse(cur);
        }
        std::shared_ptr<Faculty::Doctor> &doctor_ = Mangers::DoctorManger::id_doctor_map[std::stoll(parsed[1])];
        doctor_->addCourse(cur);
        cur->setDoctor(doctor_);
    }


    std::shared_ptr<Faculty::Doctor> &Course::getDoctor(){
        return doctor;
    }

    void Course::setDoctor(const std::shared_ptr<Faculty::Doctor> &doctor) {
        Course::doctor = doctor;
    }

    const std::vector<std::shared_ptr<Faculty::Student>> &Course::getStudentsVec() const {
        return students_vec;
    }

    void Course::setStudentsVec(const std::vector<std::shared_ptr<Faculty::Student>> &studentsVec) {
        students_vec = studentsVec;
    }

    const std::string &Course::getCourseId() const {
        return courseID;
    }

    void Course::setCourseId(const std::string &courseId) {
        courseID = courseId;
    }

    const std::string &Course::getName() const {
        return name;
    }

    void Course::setName(const std::string &Name) {
        Course::name = Name;
    }

    void Course::addStudent(std::shared_ptr<Faculty::Student> &student) {
        students_vec.push_back(student);
    }
    std::string Course::ToString() {
        std::vector<string> ent;
        ent.push_back(this->courseID);
        ent.push_back(std::to_string(this->doctor->getId()));
        ent.push_back(this->name);
        for (const auto &student_: this->students_vec) {
            ent.push_back(std::to_string(student_->getId()));
        }
        return Helper::makeEntity(ent,',');
    }
    bool Course::operator==(std::shared_ptr<Course> course) {
        return (this->courseID == course->courseID);
    }

    const std::vector<std::shared_ptr<Assignment>> &Course::getAssignmentsVec() const {
        return assignments_vec;
    }
    void Course::addAssignment(std::shared_ptr<Material::Assignment> &assignment) {
        assignments_vec.push_back(assignment);
    }
    std::pair<double,int> Course::getGradesForStudent(std::shared_ptr<Faculty::Student> &student) {
        double g = 0;
        int cnt = 0;
        for (const auto &assign: assignments_vec) {
            for (const auto &solution: assign->getSolutions()) {
                if(solution->getStudent() == student) g += solution->getGrade(),++cnt;
            }
        }
        return {g,cnt};
    }

}// namespace Material