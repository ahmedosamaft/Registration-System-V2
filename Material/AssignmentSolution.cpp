//
// Created by andro on 8/20/2023.
//

#include "AssignmentSolution.h"

#include "../Characters/Student.h"
#include "../Helper.h"
#include "../Mangers/StudentManger.h"
#include "../Mangers/AssignmentManger.h"
#include <utility>

namespace Material {
    AssignmentSolution::AssignmentSolution(long long int id, const std::shared_ptr<Assignment> &assignment, string answer) : id(id), assignment(assignment), answer(std::move(answer)), grade(0), is_graded(false) {}
    long long int AssignmentSolution::getId() const {
        return id;
    }

    void AssignmentSolution::setId(long long int id) {
        AssignmentSolution::id = id;
    }

    const std::shared_ptr<Faculty::Student> &AssignmentSolution::getStudent() const {
        return student;
    }

    void AssignmentSolution::setStudent(const std::shared_ptr<Faculty::Student> &student) {
        AssignmentSolution::student = student;
    }

    const std::shared_ptr<Assignment> &AssignmentSolution::getAssignment() const {
        return assignment;
    }

    void AssignmentSolution::setAssignment(const std::shared_ptr<Assignment> &assignment) {
        AssignmentSolution::assignment = assignment;
    }

    const string &AssignmentSolution::getAnswer() const {
        return answer;
    }

    void AssignmentSolution::setAnswer(const string &answer) {
        AssignmentSolution::answer = answer;
    }

    bool AssignmentSolution::isGraded() const {
        return is_graded;
    }

    void AssignmentSolution::setIsGraded(bool isGraded) {
        AssignmentSolution::is_graded = isGraded;
    }

    double AssignmentSolution::getGrade() const {
        return grade;
    }

    void AssignmentSolution::setGrade(double grade) {
        AssignmentSolution::grade = grade;
    }

    std::string AssignmentSolution::ToString() {
        std::vector<std::string> ent;
        ent.push_back(std::to_string(this->id));
        ent.push_back(std::to_string(this->student->getId()));
        ent.push_back(std::to_string(this->assignment->getId()));
        ent.push_back(this->answer);
        ent.push_back(std::to_string(this->is_graded));
        ent.push_back(std::to_string(this->grade));
        return Helper::makeEntity(ent, ',');
    }

    AssignmentSolution::AssignmentSolution(std::string line) {
        std::vector<string> parsed = Helper::parseLine(line,',');
        this->id = std::stoll(parsed[0]);
        /// Must Read Assignments & Students Before Read
        this->student = Mangers::StudentManger::id_student_map[std::stoll(parsed[1])];
        this->assignment = Mangers::AssignmentManger::id_assignment_map[std::stoll(parsed[2])];
        this->answer = parsed[3];
        this->is_graded = std::stoi(parsed[4]);
        this->grade = std::stod(parsed[5]);
    }
}// namespace Material