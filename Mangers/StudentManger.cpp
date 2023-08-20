//
// Created by andro on 8/18/2023.
//

#include "StudentManger.h"
#include "../Characters/Doctor.h"
#include "../Helper.h"
#include "../Material/Assignment.h"
#include "AssignmentManger.h"
#include "CourseManger.h"
#include "fstream"
#include "iostream"
#include <cassert>
#include <memory>
#include <set>
namespace Mangers {

    std::shared_ptr<Faculty::Student> StudentManger::current_student{new Faculty::Student()};
    long long StudentManger::lastId = 0;
    std::map<long long, std::shared_ptr<Faculty::Student>> StudentManger::id_student_map{std::map<long long, std::shared_ptr<Faculty::Student>>()};
    std::vector<std::shared_ptr<Faculty::Student>> StudentManger::all_students{std::vector<std::shared_ptr<Faculty::Student>>()};
    std::string StudentManger::studentDir = ".\\Database\\Students.txt";

    void StudentManger::TakeControl(string &username, string &password) {
        StudentManger::getUser(username, password);
        using namespace std;
        cout << "Welcome " + current_student->getName() + ". You are logged in!\n";
        vector<string> menu = {"List My Courses", "Register in Course", "View Course", "Grades Report", "Log out"};
        while (true) {
            int option = Helper::RunMenu(menu);
            if (option == 1)
                StudentManger::ListMyCourses();
            else if (option == 2)
                StudentManger::RegisterInCourse();
            else if (option == 3)
                StudentManger::ViewCourse();
            else if (option == 4)
                StudentManger::ShowGradesReport();
            else
                break;
        }
    }

    void StudentManger::ListMyCourses() {
        using namespace std;
        int pos = 1;
        for (const std::shared_ptr<Material::Course> &course: current_student->getRegisteredCourse()) {
            cout << '\t' << pos++ << " - "
                 << "Course Code '" << course->getCourseId() << "' - Name: " << course->getName() <<  " - Taught by dr/" << course->getDoctor()->getName() << endl;
        }
    }

    void StudentManger::RegisterInCourse() {
        std::vector<std::shared_ptr<Material::Course>> unregisteredCourses = StudentManger::getComplimentCourses();
        if (unregisteredCourses.empty()) {
            std::cout << "Already Registered in all Courses!\n";
            return;
        }
        int ind = 1;
        for (const auto &unregisteredCourse: unregisteredCourses) {
            std::cout << '\t' << ind++ << " - Course code: " << unregisteredCourse->getCourseId() << " - taught by dr/" << unregisteredCourse->getDoctor()->getName() << std::endl;
        }
        std::cout << "Choice >> ";
        int choose;
        std::cin >> choose;
        /// (Segmentation Error) out of bounds
        assert(choose >= 1 && choose <= unregisteredCourses.size());
        std::shared_ptr<Material::Course> &chosen = unregisteredCourses[choose - 1];
        chosen->addStudent(current_student);
        current_student->addCourse(chosen);
        CourseManger::reloadCourses();
    }

    void StudentManger::ViewCourse() {
        int ind = 1;
        for (const auto &course: current_student->getRegisteredCourse()) {
            std::cout << '\t' << ind++ << " - Course code: " << course->getCourseId() << " - taught by dr/" << course->getDoctor()->getName() << std::endl;
        }
        std::cout << "Choose course to show details >> ";
        int option;
        std::cin >> option;
        /// (Segmentation Error) out of bounds
        assert(option >= 1 && option <= current_student->getRegisteredCourse().size());
        std::shared_ptr<Material::Course> chosen = (current_student->getRegisteredCourse())[option - 1];
        std::cout << "Course code" << chosen->getCourseId() << " - Assignments:\n";
        ind = 1;
        if (chosen->getAssignmentsVec().empty()) {
            std::cout << "\tNo Details to Show!\n";
            return;
        }
        for (const auto &assign: chosen->getAssignmentsVec()) {
            std::cout << "\t" << ind++ << " - Assignment" << std::endl;
        }
        std::cout << "Choice >> ";
        std::cin >> option;
        assert(option >= 1 && option <= chosen->getAssignmentsVec().size());
        std::shared_ptr<Material::Assignment> assignment = chosen->getAssignmentsVec()[option - 1];
        std::shared_ptr<Material::AssignmentSolution> solution = nullptr;
        for (const auto &sol: assignment->getSolutions()) {
            if (sol->getStudent() == current_student) {
                solution = sol;
                break;
            }
        }
        if (!solution) {
            StudentManger::submitSolution(assignment, solution);
        } else {
            std::cout << "\t Submitted - " << (solution->isGraded() ? std::to_string(solution->getGrade()) : "NA") << " / " << assignment->getMaxGrade() << "\n"
                      << "\t answer: " << solution->getAnswer() << ".\n";
        }
    }

    void StudentManger::ShowGradesReport() {
        const std::vector<std::shared_ptr<Material::Course>> &reg_courses = current_student->getRegisteredCourse();
        int ind = 0;
        for (const auto &regCourse: reg_courses) {
            std::pair<double, int> g = regCourse->getGradesForStudent(current_student);
            std::cout << "\t" << ++ind << " - Course code " << regCourse->getCourseId() << " - Total Submitted Assignments: " << g.second << " - Total Grade: " << g.first << std::endl;
        }
    }

    void StudentManger::submitSolution(std::shared_ptr<Material::Assignment> &assignment, std::shared_ptr<Material::AssignmentSolution> &solution) {
        std::cout << "Not Submitted - NA / " << assignment->getMaxGrade() << std::endl;
        std::cout << "[Y / N] to Submit answer >> ";
        char op;
        std::cin >> op;
        assert(op == 'Y' || op == 'N' || op == 'n' || op == 'y');
        if (op == 'y' || op == 'Y') {
            string ans;
            std::cout << "Enter Answer >> ";
            std::cin.ignore();
            std::getline(std::cin, ans);
            solution = std::make_shared<Material::AssignmentSolution>(++Mangers::AssignmentManger::lastId_solution, assignment, ans);
            assignment->addSolution(solution);
            solution->setStudent(StudentManger::current_student);
            AssignmentManger::all_solutions.push_back(solution);
            AssignmentManger::id_solution_map[solution->getId()] = solution;
            AssignmentManger::reloadSolutions();
        }
    }

    bool StudentManger::isValidUser(std::string &username, std::string &password) {
        for (const auto &student: StudentManger::all_students)
            if (student->equals(username, password)) return true;
        return false;
    }

    void StudentManger::getUser(std::string &username, std::string &password) {
        for (auto &student: StudentManger::all_students)
            if (student->equals(username, password)) StudentManger::current_student = student;
    }

    void StudentManger::readUsers() {
        string line;
        std::ifstream fin(StudentManger::studentDir);
        assert(!fin.fail());
        StudentManger::all_students.clear();
        StudentManger::id_student_map.clear();
        while (std::getline(fin, line)) {
            std::shared_ptr<Faculty::Student> student{new Faculty::Student(line)};
            Mangers::StudentManger::lastId = std::max(lastId, student->getId());
            StudentManger::all_students.push_back(student);
        }
        for (const auto &student: all_students)
            id_student_map[student->getId()] = student;
        fin.close();
    }

    std::vector<std::shared_ptr<Material::Course>> StudentManger::getComplimentCourses() {
        std::vector<std::shared_ptr<Material::Course>> ret;
        std::vector<std::shared_ptr<Material::Course>> registered = current_student->getRegisteredCourse();
        /// O(N^2) but it's not a big problem because there aren't a lot of courses
        for (const auto &course: CourseManger::all_courses) {
            bool notRegistered = true;
            for (const auto &reg_course: registered) {
                if (reg_course == course) notRegistered = false;
            }
            if (notRegistered)
                ret.push_back(course);
        }
        return ret;
    }

}// namespace Mangers