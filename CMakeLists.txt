cmake_minimum_required(VERSION 3.25)
project(Registration_System_V2)

set(CMAKE_CXX_STANDARD 17)

add_executable(Registration_System_V2 main.cpp UserFlowController.cpp UserFlowController.h Characters/Student.cpp Characters/Student.h Characters/Doctor.cpp Characters/Doctor.h Characters/Person.cpp Characters/Person.h Material/Course.cpp Material/Course.h Mangers/StudentManger.cpp Mangers/StudentManger.h Helper.cpp Helper.h Mangers/DoctorManger.cpp Mangers/DoctorManger.h Mangers/CourseManger.cpp Mangers/CourseManger.h Material/Assignment.cpp Material/Assignment.h Material/AssignmentSolution.cpp Material/AssignmentSolution.h Mangers/AssignmentManger.cpp Mangers/AssignmentManger.h Mangers/AssignmentManger.cpp)
