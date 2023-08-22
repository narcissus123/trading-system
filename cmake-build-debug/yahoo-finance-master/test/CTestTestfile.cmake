# CMake generated Testfile for 
# Source directory: /Users/hamidzargar/CLionProjects/tradingsystem/yahoo-finance-master/test
# Build directory: /Users/hamidzargar/CLionProjects/tradingsystem/cmake-build-debug/yahoo-finance-master/test
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(quote_test "/Users/hamidzargar/CLionProjects/tradingsystem/cmake-build-debug/yahoo-finance-master/test/quote_test")
set_tests_properties(quote_test PROPERTIES  _BACKTRACE_TRIPLES "/Users/hamidzargar/CLionProjects/tradingsystem/yahoo-finance-master/test/CMakeLists.txt;35;add_test;/Users/hamidzargar/CLionProjects/tradingsystem/yahoo-finance-master/test/CMakeLists.txt;0;")
add_test(time_utils_test "/Users/hamidzargar/CLionProjects/tradingsystem/cmake-build-debug/yahoo-finance-master/test/time_utils_test")
set_tests_properties(time_utils_test PROPERTIES  _BACKTRACE_TRIPLES "/Users/hamidzargar/CLionProjects/tradingsystem/yahoo-finance-master/test/CMakeLists.txt;35;add_test;/Users/hamidzargar/CLionProjects/tradingsystem/yahoo-finance-master/test/CMakeLists.txt;0;")
subdirs("googletest-build")
