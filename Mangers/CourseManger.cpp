//
// Created by andro on 8/18/2023.
//

#include "CourseManger.h"
#include <cassert>
#include <fstream>
#include <string>

namespace Mangers {
    std::string CourseManger::coursesDir = ".\\Database\\Courses.txt";
    std::map<std::string, std::shared_ptr<Material::Course>> CourseManger::id_course_map{std::map<std::string, std::shared_ptr<Material::Course>>()};
    std::vector<std::shared_ptr<Material::Course>> CourseManger::all_courses{std::vector<std::shared_ptr<Material::Course>>()};
    void CourseManger::readCourses() {
        using namespace std;
        string line;
        std::ifstream fin(CourseManger::coursesDir);
        CourseManger::all_courses.clear();
        CourseManger::id_course_map.clear();
        while (std::getline(fin, line)) {
            std::shared_ptr<Material::Course> course{new Material::Course(line)};
            CourseManger::id_course_map[course->getCourseId()] = course;
            CourseManger::all_courses.push_back(course);
        }
        fin.close();
    }
    void CourseManger::reloadCourses() {
        std::ofstream fout(CourseManger::coursesDir,std::ios::trunc | std::ios::out);
        assert(!fout.fail());
        for (const auto &ent: CourseManger::all_courses) {
            fout << ent->ToString() << std::endl;
        }
        fout.close();
    }
}// namespace Mangers