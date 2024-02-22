# Copyright (c) 2022 船山信息 chuanshaninfo.com
# OkEDU-Classroom is licensed under Mulan PubL v2.
# You can use this software according to the terms and conditions of the Mulan PubL v2.
# You may obtain a copy of Mulan PubL v2 at:
# http://license.coscl.org.cn/MulanPubL-2.0
# THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
# EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
# MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
# See the Mulan PubL v2 for more details.
#
# ###############################################################################
#
# :: Testing
#
# ###############################################################################
message(STATUS "======enable_testing======")
enable_testing()
message(STATUS "PROJECT_NAME=" ${PROJECT_NAME})

function(auto_test subsystem module)
  add_executable(test_${module}
    test/${subsystem}/${module}_test.cpp)
  target_link_libraries(test_${module}
    ${PROJECT_NAME}_static
    ${CHECK_LIBRARIES}
    Qt5::Test)
  add_test(
    NAME test_${module}
    COMMAND ${TEST_CROSSCOMPILING_EMULATOR} test_${module})
endfunction()

# auto_test(classroom application)

if(UNIX)
  # auto_test(platform posixsignalnotifier)
endif()
