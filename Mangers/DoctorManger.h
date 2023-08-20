//
// Created by andro on 8/18/2023.
//

#ifndef REGISTRATION_SYSTEM_V2_DOCTORMANGER_H
#define REGISTRATION_SYSTEM_V2_DOCTORMANGER_H

#include "../Characters/Doctor.h"
#include <map>
#include <string>

namespace Mangers {

    class DoctorManger {
    public:
        static long long lastId;
        static std::string doctorDir;
        static std::shared_ptr<Faculty::Doctor> current_doctor;
        static std::map<long long, std::shared_ptr<Faculty::Doctor>> id_doctor_map;
        static std::vector<std::shared_ptr<Faculty::Doctor>> all_doctors;

    public:
        static bool isValidUser(string &, string &);
        static void readUsers();
        static void getUser(string &, string &);
        static void takeControl(string &, string &);
        static void ListMyCourses();
        static void AddAssignment();
        static void ViewCourse();
    };

}// namespace Mangers

#endif//REGISTRATION_SYSTEM_V2_DOCTORMANGER_H
