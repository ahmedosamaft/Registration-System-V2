//
// Created by andro on 8/18/2023.
//

#include "UserFlowController.h"
#include "Helper.h"
#include "Mangers/AssignmentManger.h"
#include "Mangers/CourseManger.h"
#include "Mangers/DoctorManger.h"
#include "Mangers/StudentManger.h"


void UserFlowController::ShowMainMenu() {
    std::vector<std::string> menu = {"Login", "Sign up", "Exit"};
    Mangers::StudentManger::readUsers();
    Mangers::DoctorManger::readUsers();
    Mangers::CourseManger::readCourses();
    Mangers::AssignmentManger::readAssignments();
    Mangers::AssignmentManger::readAssignmentsSolution();
    while (true) {
        int choice = Helper::RunMenu(menu);
        if (choice == 1)
            DoLogin();
        else
            break;
    }
}

void UserFlowController::DoLogin() {
    printf("\nPlease enter username and password >> ");
    std::string username;
    std::string password;
    std::cin >> username >> password;
    if (Mangers::StudentManger::isValidUser(username, password))
        Mangers::StudentManger::TakeControl(username, password);
    else if(Mangers::DoctorManger::isValidUser(username, password))
        Mangers::DoctorManger::takeControl(username, password);
    else
        return;
}
