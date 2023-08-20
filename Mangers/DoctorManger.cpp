//
// Created by andro on 8/18/2023.
//

#include "DoctorManger.h"
#include "../Helper.h"
#include "../Mangers/StudentManger.h"
#include "AssignmentManger.h"
#include <cassert>
#include <fstream>
#include <iostream>

namespace Mangers {
    std::shared_ptr<Faculty::Doctor> DoctorManger::current_doctor{new Faculty::Doctor()};
    long long DoctorManger::lastId = 0;
    std::map<long long, std::shared_ptr<Faculty::Doctor>> DoctorManger::id_doctor_map{std::map<long long, std::shared_ptr<Faculty::Doctor>>()};
    std::vector<std::shared_ptr<Faculty::Doctor>> DoctorManger::all_doctors{std::vector<std::shared_ptr<Faculty::Doctor>>()};
    std::string DoctorManger::doctorDir = ".\\Database\\Doctors.txt";

    void DoctorManger::takeControl(string &username, string &password) {
        DoctorManger::getUser(username, password);
        using namespace std;
        cout << "Welcome dr/" + current_doctor->getName() + ". You are logged in!\n";
        vector<string> menu = {"List My Courses", "Add Assignment", "View Course", "Log out"};
        while (true) {
            int option = Helper::RunMenu(menu);
            if (option == 1)
                DoctorManger::ListMyCourses();
            else if (option == 2)
                DoctorManger::AddAssignment();
            else if (option == 3)
                DoctorManger::ViewCourse();
            else
                break;
        }
    }

    void DoctorManger::ListMyCourses() {
        using namespace std;
        int pos = 1;
        for (const std::shared_ptr<Material::Course> &course: current_doctor->getTeachingCourse()) {
            cout << '\t' << pos++ << " - "
                 << "Course Code '" << course->getCourseId() << "' - Name: " << course->getName() << " - Total Registered Students: " << course->getStudentsVec().size() << endl;
        }
    }

    void DoctorManger::AddAssignment() {
        DoctorManger::ListMyCourses();
        std::cout << "Choice >> ";
        int option;
        std::cin >> option;
        assert(option >= 1 && option <= current_doctor->getTeachingCourse().size());
        std::shared_ptr<Material::Course> course = current_doctor->getTeachingCourse()[option - 1];
        std::cout << "Enter Assignment Max Grade >> ";
        double g;
        std::cin >> g;
        std::shared_ptr<Material::Assignment> assignment{new Material::Assignment(++Mangers::AssignmentManger::lastId_assignment, course, g)};
        Mangers::AssignmentManger::all_assignments.push_back(assignment);
        Mangers::AssignmentManger::id_assignment_map[assignment->getId()] = assignment;
        course->addAssignment(assignment);
        Mangers::AssignmentManger::reloadAssignments();
    }

    void DoctorManger::ViewCourse() {
        DoctorManger::ListMyCourses();
        std::cout << "Choice >> ";
        int option;
        std::cin >> option;
        assert(option >= 1 && option <= current_doctor->getTeachingCourse().size());
        std::shared_ptr<Material::Course> course = current_doctor->getTeachingCourse()[option - 1];
        std::cout << "Register Student:\n";
        int ind = 0;
        for (const auto &student: course->getStudentsVec()) {
            std::cout << "\t" << ++ind << " - Name: " << student->getName() << " - ID: " << student->getId() << std::endl;
        }
        std::cout << "Choice >> ";
        std::cin >> option;
        assert(option >= 1 && option <= course->getStudentsVec().size());
        std::shared_ptr<Faculty::Student> &student = Mangers::StudentManger::id_student_map[course->getStudentsVec()[option - 1]->getId()];
        std::vector<std::shared_ptr<Material::AssignmentSolution>> studentSolutions;
        for (const auto &solution: student->getSolutions()) {
            if (solution->getAssignment()->getCourse() == course)
                studentSolutions.push_back(solution);
        }
        if (studentSolutions.empty()) {
            std::cout << "Student has not Submitted any Assignments.\n";
            return;
        }
        ind = 0;
        for (const auto &solution: studentSolutions) {
            std::shared_ptr<Material::Assignment> assign = solution->getAssignment();
            std::cout << "\t" << ++ind << " - Grade: " << (solution->isGraded() ? std::to_string(solution->getGrade()) : "NA") << " / " << assign->getMaxGrade()
                      << " - Answer: " << solution->getAnswer() << std::endl;
        }
        std::cout << "Choice >> ";
        std::cin >> option;
        assert(option >= 1 && option <= studentSolutions.size());
        std::shared_ptr<Material::AssignmentSolution> sol = studentSolutions[option - 1];
        printf("Give a Grade out of [%f] >> ", sol->getAssignment()->getMaxGrade());
        double g;
        std::cin >> g;
        assert(g >= 0 && g <= sol->getAssignment()->getMaxGrade());
        sol->setGrade(g);
        Mangers::AssignmentManger::readAssignmentsSolution();
    }

    bool DoctorManger::isValidUser(std::string &username, std::string &password) {
        for (const auto &doctor: DoctorManger::all_doctors)
            if (doctor->equals(username, password)) return true;
        return false;
    }

    void DoctorManger::getUser(std::string &username, std::string &password) {
        for (auto &doctor: DoctorManger::all_doctors)
            if (doctor->equals(username, password)) DoctorManger::current_doctor = doctor;
    }

    void DoctorManger::readUsers() {
        string line;
        std::ifstream fin(DoctorManger::doctorDir);
        DoctorManger::all_doctors.clear();
        DoctorManger::id_doctor_map.clear();
        while (std::getline(fin, line)) {
            std::shared_ptr<Faculty::Doctor> doctor{new Faculty::Doctor(line)};
            Mangers::DoctorManger::lastId = std::max(lastId, doctor->getId());
            DoctorManger::all_doctors.push_back(doctor);
        }
        for (const auto &doctor: all_doctors)
            id_doctor_map[doctor->getId()] = doctor;
        fin.close();
    }
}// namespace Mangers