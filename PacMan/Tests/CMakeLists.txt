enable_testing()

find_package(Qt6 REQUIRED COMPONENTS Test)

function(SETUP_TESTS)
    foreach(_testname ${ARGN})
        add_executable(${_testname}
            tst_${_testname}.cpp
        )
        add_test(NAME ${_testname} COMMAND ${_testname} WORKING_DIRECTORY "${CMAKE_BINARY_DIR}")
        target_link_libraries(${_testname} Qt${QT_MAJOR_VERISION}::Test PacManLib)
    endforeach()
endfunction()

SETUP_TESTS(
   Test
)
