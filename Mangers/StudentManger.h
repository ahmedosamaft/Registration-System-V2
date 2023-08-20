//
// Created by andro on 8/18/2023.
//

#ifndef REGISTRATION_SYSTEM_V2_STUDENTMANGER_H
#define REGISTRATION_SYSTEM_V2_STUDENTMANGER_H
#include "../Characters/Student.h"
#include <map>

namespace Mangers {
    class StudentManger {

    public:
        static long long lastId;
        static std::string studentDir;
        static std::shared_ptr<Faculty::Student> current_student;
        static std::map<long long, std::shared_ptr<Faculty::Student>> id_student_map;
        static std::vector<std::shared_ptr<Faculty::Student>> all_students;

    public:
        static bool isValidUser(string &, string &);
        static void readUsers();
        static void getUser(string &, string &);
        static void TakeControl(string &username, string &password);
        static void ListMyCourses();
        static void RegisterInCourse();
        static std::vector<std::shared_ptr<Material::Course>> getComplimentCourses();
        static void ViewCourse();
        static void submitSolution(std::shared_ptr<Material::Assignment> &assignment, std::shared_ptr<Material::AssignmentSolution> &solution);
        static void ShowGradesReport();
    };
}// namespace Mangers


#endif//REGISTRATION_SYSTEM_V2_STUDENTMANGER_H
