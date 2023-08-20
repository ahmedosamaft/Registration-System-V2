//
// Created by andro on 8/20/2023.
//

#ifndef REGISTRATION_SYSTEM_V2_ASSIGNMENTMANGER_H
#define REGISTRATION_SYSTEM_V2_ASSIGNMENTMANGER_H

#include "../Material/AssignmentSolution.h"
#include "../Material/Assignment.h"
#include <map>
#include <memory>
namespace Mangers {

    class AssignmentManger {
    public:
        static long long lastId_assignment;
        static long long lastId_solution;
        static std::string assignmentDir;
        static std::string assignmentSolutionDir;
        static std::map<long long, std::shared_ptr<Material::Assignment>> id_assignment_map;
        static std::map<long long, std::shared_ptr<Material::AssignmentSolution>> id_solution_map;
        static std::vector<std::shared_ptr<Material::Assignment>> all_assignments;
        static std::vector<std::shared_ptr<Material::AssignmentSolution>> all_solutions;

        static void readAssignments();
        static void readAssignmentsSolution();
        static void reloadSolutions();
        static void reloadAssignments();
    };

}// namespace Mangers

#endif//REGISTRATION_SYSTEM_V2_ASSIGNMENTMANGER_H
