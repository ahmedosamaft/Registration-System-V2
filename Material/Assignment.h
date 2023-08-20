//
// Created by andro on 8/20/2023.
//

#ifndef REGISTRATION_SYSTEM_V2_ASSIGNMENT_H
#define REGISTRATION_SYSTEM_V2_ASSIGNMENT_H


#include "Course.h"
#include "AssignmentSolution.h"


namespace Material{
    class Assignment {
    private:
        long long id{};
        std::shared_ptr<Course> course;
        double maxGrade;
        std::vector<std::shared_ptr<AssignmentSolution>> solutions;

    public:
        Assignment();
        explicit Assignment(std::string& line);
        Assignment(long long id,std::shared_ptr<Course>& course_,double max_grade);

    public:
        void setId(long long int id);
        const std::shared_ptr<Course> &getCourse() const;
        void setCourse(const std::shared_ptr<Course> &course);
        const std::vector<std::shared_ptr<AssignmentSolution>> &getSolutions() const;
        void addSolution(const std::shared_ptr<AssignmentSolution> &solution);
        double getMaxGrade() const;
        void setMaxGrade(double maxGrade);
        std::string ToString();
        long long int getId() const;
        bool operator ==(long long) const;

    };
}


#endif//REGISTRATION_SYSTEM_V2_ASSIGNMENT_H
