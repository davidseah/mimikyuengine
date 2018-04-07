

set(command "D:/Tool/Common/CMake/Cmake-3.3.2/CMake/bin/cmake.exe;-P;D:/RANDD/OpenGL_Testframe/OpenGL_TFF/assimp-3.3.1/project_generated/test/gtest/tmp/gtest-gitclone.cmake")
execute_process(
  COMMAND ${command}
  RESULT_VARIABLE result
  OUTPUT_FILE "D:/RANDD/OpenGL_Testframe/OpenGL_TFF/assimp-3.3.1/project_generated/test/gtest/src/gtest-stamp/gtest-download-out.log"
  ERROR_FILE "D:/RANDD/OpenGL_Testframe/OpenGL_TFF/assimp-3.3.1/project_generated/test/gtest/src/gtest-stamp/gtest-download-err.log"
  )
if(result)
  set(msg "Command failed: ${result}\n")
  foreach(arg IN LISTS command)
    set(msg "${msg} '${arg}'")
  endforeach()
  set(msg "${msg}\nSee also\n  D:/RANDD/OpenGL_Testframe/OpenGL_TFF/assimp-3.3.1/project_generated/test/gtest/src/gtest-stamp/gtest-download-*.log")
  message(FATAL_ERROR "${msg}")
else()
  set(msg "gtest download command succeeded.  See also D:/RANDD/OpenGL_Testframe/OpenGL_TFF/assimp-3.3.1/project_generated/test/gtest/src/gtest-stamp/gtest-download-*.log")
  message(STATUS "${msg}")
endif()
