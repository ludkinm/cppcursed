add_executable(unit_tests unit_tests.cc)

target_link_libraries(unit_tests PUBLIC Curserd)

add_test(NAME unit_tests COMMAND unit_tests)
