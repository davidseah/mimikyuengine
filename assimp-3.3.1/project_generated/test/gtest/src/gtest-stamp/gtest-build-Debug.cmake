

set(command "D:/Tool/Common/CMake/Cmake-3.3.2/CMake/bin/cmake.exe;--build;.;--config;${config}")
execute_process(
  COMMAND ${command}
  RESULT_VARIABLE result
  OUTPUT_FILE "D:/RANDD/OpenGL_Testframe/OpenGL_TFF/assimp-3.3.1/project_generated/test/gtest/src/gtest-stamp/gtest-build-out.log"
  ERROR_FILE "D:/RANDD/OpenGL_Testframe/OpenGL_TFF/assimp-3.3.1/project_generated/test/gtest/src/gtest-stamp/gtest-build-err.log"
  )
if(result)
  set(msg "Command failed: ${result}\n")
  foreach(arg IN LISTS command)
    set(msg "${msg} '${arg}'")
  endforeach()
  set(msg "${msg}\nSee also\n  D:/RANDD/OpenGL_Testframe/OpenGL_TFF/assimp-3.3.1/project_generated/test/gtest/src/gtest-stamp/gtest-build-*.log")
  message(FATAL_ERROR "${msg}")
else()
  set(msg "gtest build command succeeded.  See also D:/RANDD/OpenGL_Testframe/OpenGL_TFF/assimp-3.3.1/project_generated/test/gtest/src/gtest-stamp/gtest-build-*.log")
  message(STATUS "${msg}")
endif()
