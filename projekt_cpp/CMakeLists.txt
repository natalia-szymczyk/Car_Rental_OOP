cmake_minimum_required(VERSION 3.10)

project(Car_Rental VERSION 1.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(SOURCES main.cpp Accident.cpp Budget.cpp Bus.cpp Car.cpp Date.cpp Employee.cpp Employees.cpp Fleet.cpp Loan.cpp Text.cpp Vehicle.cpp)

add_executable (Car_Rental main.cpp Accident.cpp Budget.cpp Bus.cpp Car.cpp Date.cpp Employee.cpp Employees.cpp Fleet.cpp Loan.cpp Text.cpp Vehicle.cpp)

