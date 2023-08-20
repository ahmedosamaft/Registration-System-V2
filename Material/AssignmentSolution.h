//
// Created by andro on 8/20/2023.
//

#ifndef REGISTRATION_SYSTEM_V2_ASSIGNMENTSOLUTION_H
#define REGISTRATION_SYSTEM_V2_ASSIGNMENTSOLUTION_H

#include <memory>
#include <string>
namespace Faculty {
    class Student;
}

namespace Material {
    class Assignment;
    class AssignmentSolution {
    private:
        long long id;
        std::shared_ptr<Faculty::Student> student;
        std::shared_ptr<Assignment> assignment;
        std::string answer;
        bool is_graded;
        double grade;

    public:
        AssignmentSolution(long long int id, const std::shared_ptr<Assignment> &assignment, std::string answer);
        explicit AssignmentSolution(std::string line);

    public:
        long long int getId() const;
        void setId(long long int id);
        const std::shared_ptr<Faculty::Student> &getStudent() const;
        void setStudent(const std::shared_ptr<Faculty::Student> &student);
        const std::shared_ptr<Assignment> &getAssignment() const;
        void setAssignment(const std::shared_ptr<Assignment> &assignment);
        const std::string &getAnswer() const;
        void setAnswer(const std::string &answer);
        bool isGraded() const;
        void setIsGraded(bool isGraded);
        double getGrade() const;
        void setGrade(double grade);
        std::string ToString();

    };

}// namespace Material

#endif//REGISTRATION_SYSTEM_V2_ASSIGNMENTSOLUTION_H
