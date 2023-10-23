enable_testing()

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Test)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Test)

function(SETUP_TESTS)
    foreach(_testname ${ARGN})
        add_executable(${_testname}
            tst_${_testname}.cpp
        )
        add_test(NAME ${_testname} COMMAND ${_testname})
        target_link_libraries(${_testname} Qt${QT_MAJOR_VERISION}::Test PacManLib)
    endforeach()
endfunction()

SETUP_TESTS(
   Test
)
