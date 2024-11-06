#include "oatpp-test/UnitTest.hpp"
#include "oatpp/core/base/Environment.hpp"
#include "NoteControllerTest.hpp"

#include <iostream>

namespace {

    void runTests() {

        OATPP_RUN_TEST(NoteControllerTest);

    }

}

int main() {

    oatpp::base::Environment::init();

    runTests();

    OATPP_ASSERT(oatpp::base::Environment::getObjectsCount() == 0);

    oatpp::base::Environment::destroy();

    return 0;
}
