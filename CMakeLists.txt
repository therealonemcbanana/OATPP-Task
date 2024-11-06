cmake_minimum_required(VERSION 3.1)
project(Task)

set(CMAKE_CXX_STANDARD 11)

add_library(Components
        src/controller/NoteController.hpp
        src/db/NoteDb.hpp
        src/dto/StatusDto.hpp
        src/dto/NoteDto.hpp
        src/service/NoteService.cpp
        src/service/NoteService.hpp
        src/AppComponent.hpp
        src/DatabaseComponent.hpp
        src/SwaggerComponent.hpp
        src/ErrorHandler.hpp
        src/ErrorHandler.cpp)

target_include_directories(Components PUBLIC src)

find_package(oatpp          1.3.0 REQUIRED)
find_package(oatpp-swagger  1.3.0 REQUIRED)
find_package(oatpp-sqlite   1.3.0 REQUIRED)

target_link_libraries(Components
        PUBLIC oatpp::oatpp
        PUBLIC oatpp::oatpp-swagger
        PUBLIC oatpp::oatpp-sqlite
)

add_definitions(
        -DOATPP_SWAGGER_RES_PATH="${oatpp-swagger_INCLUDE_DIRS}/../bin/oatpp-swagger/res"
        -DDATABASE_FILE="${CMAKE_CURRENT_SOURCE_DIR}/db.sqlite"
        -DTESTDATABASE_FILE="${CMAKE_CURRENT_SOURCE_DIR}/test-db.sqlite"
        -DDATABASE_MIGRATIONS="${CMAKE_CURRENT_SOURCE_DIR}/sql"
)

if(CMAKE_SYSTEM_NAME MATCHES Linux)
    find_package(Threads REQUIRED)
    target_link_libraries(Components INTERFACE Threads::Threads ${CMAKE_DL_LIBS})
endif()

add_executable(Task src/main.cpp)
target_link_libraries(Task Components)

add_executable(Test
        test/tests.cpp
        test/app/TestClient.hpp
        test/app/TestDatabaseComponent.hpp
        test/app/TestComponent.hpp
        test/NoteControllerTest.hpp
        test/NoteControllerTest.cpp)
target_link_libraries(Test Components)

enable_testing()
add_test(project-tests Test)
