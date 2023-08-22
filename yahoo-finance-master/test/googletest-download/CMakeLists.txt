project(googletest-download NONE)

include(ExternalProject)
ExternalProject_Add(googletest
    GIT_REPOSITORY      https://github.com/google/googletest.git
    GIT_TAG             master
    SOURCE_DIR          "/Users/hamidzargar/CLionProjects/tradingsystem/yahoo-finance-master/test/googletest-src"
    BINARY_DIR          "/Users/hamidzargar/CLionProjects/tradingsystem/yahoo-finance-master/test/googletest-build"
    CONFIGURE_COMMAND   ""
    BUILD_COMMAND       ""
    INSTALL_COMMAND     ""
    TEST_COMMAND        ""
)
