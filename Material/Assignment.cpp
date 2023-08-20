//
// Created by andro on 8/20/2023.
//

#include "Assignment.h"
#include "../Mangers/CourseManger.h"
#include "../Helper.h"

namespace Material {


    Assignment::Assignment() = default;
    Assignment::Assignment(long long int id, std::shared_ptr<Course> &course_, double max_grade) : id(id), course(course_), maxGrade(max_grade) {}
    Assignment::Assignment(string &line) {
        std::vector<string> parsed = Helper::parseLine(line,',');
        this->id = std::stoll(parsed[0]);
        /// Must Read Courses Before Read Assignments
        this->course = Mangers::CourseManger::id_course_map[parsed[1]];
        this->maxGrade = std::stod(parsed[2]);
    }


    const std::shared_ptr<Course> &Assignment::getCourse() const {
        return course;
    }

    void Assignment::setCourse(const std::shared_ptr<Course> &course_) {
        Assignment::course = course_;
    }

    const std::vector<std::shared_ptr<AssignmentSolution>> &Assignment::getSolutions() const {
        return solutions;
    }

    void Assignment::addSolution(const std::shared_ptr<AssignmentSolution> &solution) {
        Assignment::solutions.push_back(solution);
    }

    double Assignment::getMaxGrade() const {
        return maxGrade;
    }

    void Assignment::setMaxGrade(double maxGrade) {
        Assignment::maxGrade = maxGrade;
    }

    std::string Assignment::ToString() {
        std::vector<std::string> ent;
        ent.push_back(std::to_string(this->id));
        ent.push_back(this->course->getCourseId());
        ent.push_back(std::to_string(this->maxGrade));
//        for (const auto &sol: solutions) {
//            ent.push_back(std::to_string(sol->getId()));
//        }
        return Helper::makeEntity(ent, ',');
    }

    void Assignment::setId(long long int id) {
        Assignment::id = id;
    }

    long long int Assignment::getId() const {
        return id;
    }

    bool Assignment::operator ==(long long int Id) const  {
        return this->id == Id;
    }
}// namespace Material