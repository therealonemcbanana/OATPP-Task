#ifndef NOTECONTROLLERTEST_HPP
#define NOTECONTROLLERTEST_HPP

#include "oatpp-test/UnitTest.hpp"

class NoteControllerTest : public oatpp::test::UnitTest {
public:
    NoteControllerTest() : oatpp::test::UnitTest("TEST[NoteControllerTest]")
    {}

    void onRun() override;
};

#endif
