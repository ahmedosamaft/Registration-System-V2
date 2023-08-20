//
// Created by andro on 8/20/2023.
//

#include "AssignmentManger.h"
#include "StudentManger.h"
#include <cassert>
#include <fstream>

namespace Mangers {

    long long AssignmentManger::lastId_assignment = 0;
    long long AssignmentManger::lastId_solution = 0;
    std::string AssignmentManger::assignmentDir = ".\\Database\\Assignments.txt";
    std::string AssignmentManger::assignmentSolutionDir = ".\\Database\\Solutions.txt";
    std::map<long long, std::shared_ptr<Material::Assignment>> AssignmentManger::id_assignment_map = std::map<long long, std::shared_ptr<Material::Assignment>>();
    std::vector<std::shared_ptr<Material::Assignment>> AssignmentManger::all_assignments = std::vector<std::shared_ptr<Material::Assignment>>();
    std::map<long long, std::shared_ptr<Material::AssignmentSolution>> AssignmentManger::id_solution_map = std::map<long long, std::shared_ptr<Material::AssignmentSolution>>();
    std::vector<std::shared_ptr<Material::AssignmentSolution>> AssignmentManger::all_solutions = std::vector<std::shared_ptr<Material::AssignmentSolution>>();

    void AssignmentManger::readAssignments() {
        using namespace std;
        string line;
        std::ifstream fin(AssignmentManger::assignmentDir);
        assert(!fin.fail());
        AssignmentManger::all_assignments.clear();
        AssignmentManger::id_assignment_map.clear();
        while (std::getline(fin, line)) {
            std::shared_ptr<Material::Assignment> assignment{new Material::Assignment(line)};
            Mangers::AssignmentManger::lastId_assignment = std::max(lastId_assignment, assignment->getId());
            AssignmentManger::all_assignments.push_back(assignment);
            id_assignment_map[assignment->getId()] = assignment;
        }
        for (auto &assignment: all_assignments)
            assignment->getCourse()->addAssignment(assignment);
        fin.close();
    }

    void AssignmentManger::readAssignmentsSolution() {
        using namespace std;
        string line;
        std::ifstream fin(AssignmentManger::assignmentSolutionDir);
        assert(!fin.fail());
        AssignmentManger::all_solutions.clear();
        AssignmentManger::id_solution_map.clear();
        while (std::getline(fin, line)) {
            std::shared_ptr<Material::AssignmentSolution> solution{new Material::AssignmentSolution(line)};
            Mangers::AssignmentManger::lastId_solution = std::max( Mangers::AssignmentManger::lastId_solution, solution->getId());
            AssignmentManger::all_solutions.push_back(solution);
        }
        for (auto &solution: all_solutions) {
            solution->getAssignment()->addSolution(solution);
            solution->getStudent()->addSolution(solution);
        }
        fin.close();
    }

    void AssignmentManger::reloadSolutions() {
        std::ofstream fout(AssignmentManger::assignmentSolutionDir,std::ios::trunc | std::ios::out);
        assert(!fout.fail());
        for (const auto &ent: AssignmentManger::all_solutions) {
            fout << ent->ToString() << std::endl;
        }
        fout.close();
    }


    void AssignmentManger::reloadAssignments() {
        std::ofstream fout(AssignmentManger::assignmentDir,std::ios::trunc | std::ios::out);
        assert(!fout.fail());
        for (const auto &ent: AssignmentManger::all_assignments) {
            fout << ent->ToString() << std::endl;
        }
        fout.close();
    }
}// namespace Mangers