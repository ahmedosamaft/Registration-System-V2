//
// Created by andro on 8/18/2023.
//

#ifndef REGISTRATION_SYSTEM_V2_COURSEMANGER_H
#define REGISTRATION_SYSTEM_V2_COURSEMANGER_H

#include "../Material/Course.h"
#include <map>
#include <memory>

namespace Mangers {

    class CourseManger {
    public:
        static std::string coursesDir;
        static std::map<std::string , std::shared_ptr<Material::Course>> id_course_map;
        static std::vector<std::shared_ptr<Material::Course>> all_courses;
        static void readCourses();
        static void reloadCourses();

    };

}// namespace Mangers

#endif//REGISTRATION_SYSTEM_V2_COURSEMANGER_H
