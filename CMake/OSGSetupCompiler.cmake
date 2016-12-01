
MESSAGE(STATUS "Applying Compiler Defaults")

SET(OSG_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DOSG_DEBUG")
SET(OSG_C_FLAGS_DEBUG   "${CMAKE_C_FLAGS_DEBUG} -DOSG_DEBUG")

IF(UNIX)
  SET(OSG_CXX_FLAGS_DEBUG "${OSG_CXX_FLAGS_DEBUG} -D_DEBUG")
  SET(OSG_C_FLAGS_DEBUG   "${OSG_C_FLAGS_DEBUG} -D_DEBUG")
ENDIF(UNIX)

IF(APPLE AND IOS)
  SET(OSG_CXX_FLAGS_DEBUG "${OSG_CXX_FLAGS_DEBUG} -g")
  SET(OSG_C_FLAGS_DEBUG   "${OSG_C_FLAGS_DEBUG} -g")
ENDIF(APPLE AND IOS)

SET(OSG_CXX_FLAGS ${CMAKE_CXX_FLAGS})
SET(OSG_C_FLAGS   ${CMAKE_C_FLAGS})

SET(OSG_CXX_FLAGS_RELEASE ${CMAKE_CXX_FLAGS_RELEASE})
SET(OSG_C_FLAGS_RELEASE   ${CMAKE_C_FLAGS_RELEASE})

IF(APPLE AND IOS)
  SET(OSG_CXX_FLAGS_RELEASE "${OSG_CXX_FLAGS_RELEASE} -O3 -DNDEBUG")
  SET(OSG_C_FLAGS_RELEASE   "${OSG_C_FLAGS_RELEASE} -O3 -DNDEBUG")
ENDIF(APPLE AND IOS)

SET(OSG_EXE_LINKER_FLAGS    ${CMAKE_EXE_LINKER_FLAGS})
SET(OSG_SHARED_LINKER_FLAGS ${CMAKE_SHARED_LINKER_FLAGS})

IF(MSVC)

    MESSAGE(STATUS "Setup MSVC")

    # Hide unused cmake targets

    SET(CMAKE_CXX_FLAGS_MINSIZEREL
        "${CMAKE_CXX_FLAGS_MINSIZEREL}" 
        CACHE INTERNAL "")

    SET(CMAKE_CXX_FLAGS_RELWITHDEBINFO
        "${CMAKE_CXX_FLAGS_RELWITHDEBINFO}" 
        CACHE INTERNAL "")


    SET(CMAKE_C_FLAGS_MINSIZEREL
        "${CMAKE_C_FLAGS_MINSIZEREL}" 
        CACHE INTERNAL "")

    SET(CMAKE_C_FLAGS_RELWITHDEBINFO
        "${CMAKE_C_FLAGS_RELWITHDEBINFO}" 
        CACHE INTERNAL "")


    # ReleaseNoOpt

    SET(OSG_CXX_FLAGS_RELEASENOOPT "${OSG_CXX_FLAGS_DEBUG} /MP${OSG_NUM_COMPILE_PROC}")
    SET(OSG_C_FLAGS_RELEASENOOPT   "${OSG_C_FLAGS_DEBUG} /MP${OSG_NUM_COMPILE_PROC}")

    STRING(REPLACE "MDd" "MD" OSG_CXX_FLAGS_RELEASENOOPT ${OSG_CXX_FLAGS_RELEASENOOPT})
    STRING(REPLACE "MDd" "MD" OSG_C_FLAGS_RELEASENOOPT   ${OSG_C_FLAGS_RELEASENOOPT})

    STRING(REPLACE "/RTC1" "" OSG_CXX_FLAGS_RELEASENOOPT ${OSG_CXX_FLAGS_RELEASENOOPT})
    STRING(REPLACE "/RTC1" "" OSG_C_FLAGS_RELEASENOOPT   ${OSG_C_FLAGS_RELEASENOOPT})

    STRING(REPLACE "/D_DEBUG" "" OSG_CXX_FLAGS_RELEASENOOPT ${OSG_CXX_FLAGS_RELEASENOOPT})
    STRING(REPLACE "/D_DEBUG" "" OSG_C_FLAGS_RELEASENOOPT   ${OSG_C_FLAGS_RELEASENOOPT})

    # Debug

    SET(OSG_CXX_FLAGS_DEBUG "${OSG_CXX_FLAGS_DEBUG} -DOSG_DEBUGRT /MP${OSG_NUM_COMPILE_PROC}")
    SET(OSG_C_FLAGS_DEBUG   "${OSG_C_FLAGS_DEBUG} -DOSG_DEBUGRT /MP${OSG_NUM_COMPILE_PROC}")
    
    # Debug Opt

    SET(OSG_CXX_FLAGS_DEBUGOPT "${OSG_CXX_FLAGS_RELEASE} -DOSG_DEBUGRT /Zi /MP${OSG_NUM_COMPILE_PROC}")
    SET(OSG_C_FLAGS_DEBUGOPT   "${OSG_C_FLAGS_RELEASE} -DOSG_DEBUGRT /Zi /MP${OSG_NUM_COMPILE_PROC}")
    
    STRING(REPLACE "MD" "MDd" OSG_CXX_FLAGS_DEBUGOPT ${OSG_CXX_FLAGS_DEBUGOPT})
    STRING(REPLACE "MD" "MDd" OSG_C_FLAGS_DEBUGOPT   ${OSG_C_FLAGS_DEBUGOPT})

#    STRING(REPLACE "/D NDEBUG " "" OSG_CXX_FLAGS_DEBUGOPT ${OSG_CXX_FLAGS_DEBUGOPT})
#    STRING(REPLACE "/D NDEBUG " "" OSG_C_FLAGS_DEBUGOPT   ${OSG_C_FLAGS_DEBUGOPT})

    # Release

    SET(OSG_CXX_FLAGS_RELEASE "${OSG_CXX_FLAGS_RELEASE} /Zi /MP${OSG_NUM_COMPILE_PROC}")
    SET(OSG_C_FLAGS_RELEASE   "${OSG_C_FLAGS_RELEASE} /Zi /MP${OSG_NUM_COMPILE_PROC}")

    # Push to CMAKE

    SET(CMAKE_CXX_FLAGS_DEBUGOPT 
        "${OSG_CXX_FLAGS_DEBUGOPT}" 
        CACHE STRING "Flags used by the C++ compiler during maintainer builds."
        FORCE)

    SET(CMAKE_C_FLAGS_DEBUGOPT 
        "${OSG_C_FLAGS_DEBUGOPT}" 
        CACHE STRING "Flags used by the C compiler during maintainer builds."
        FORCE)

    SET(CMAKE_CXX_FLAGS_RELEASENOOPT 
        "${OSG_CXX_FLAGS_RELEASENOOPT}" 
        CACHE STRING "Flags used by the C++ compiler during maintainer builds."
        FORCE)

    SET(CMAKE_C_FLAGS_RELEASENOOPT 
        "${OSG_C_FLAGS_RELEASENOOPT}" 
        CACHE STRING "Flags used by the C compiler during maintainer builds."
        FORCE)




    # General Flags

#    STRING(REPLACE "W3"  "W1" OSG_CXX_FLAGS       ${OSG_CXX_FLAGS})
#    STRING(REPLACE "W3"  "W1" OSG_C_FLAGS         ${OSG_C_FLAGS})

    # 4290 exception spec
    # 4251 dll export
    # 4275 derived from not exported
    # 4661 template class mem func not defined
    # 4351 member init array handling
    # 4996 deprecated
    # 4231 non standard ext

    # 4244 smaller type assign
    # 4355 this before constructed
    #
    # /wd4244 /wd4355

    STRING(REPLACE "W3"  "W3 /wd4244 /wd4290 /wd4251 /wd4275 /wd4661 /wd4351 /wd4996 /wd4018 /wd4503 /wd4101 /wd4305 /wd4076 /wd4099 /wd4091 /wd4910 /wd4231 /wd4267 /wd4800" OSG_CXX_FLAGS ${OSG_CXX_FLAGS})
    STRING(REPLACE "W3"  "W3 /wd4244 /wd4290 /wd4251 /wd4275 /wd4351 /wd4996         /wd4018 /wd4503 /wd4101 /wd4305 /wd4076 /wd4099 /wd4091 /wd4910 /wd4231 /wd4267 /wd4800" OSG_C_FLAGS ${OSG_C_FLAGS})

    SET(OSG_CXX_FLAGS "/bigobj ${OSG_CXX_FLAGS} /D_WIN32_WINNT=0x0500 /DWINVER=0x0500")
    SET(OSG_C_FLAGS   "/bigobj ${OSG_C_FLAGS} /D_WIN32_WINNT=0x0500 /DWINVER=0x0500")


    # Libs

    SET(OSG_EXE_LINKER_FLAGS "${OSG_EXE_LINKER_FLAGS} /nodefaultlib") 
    SET(OSG_SHARED_LINKER_FLAGS "${OSG_SHARED_LINKER_FLAGS} /nodefaultlib") 

    SET(OSG_CXX_STANDARD_LIBRARIES "${CMAKE_CXX_STANDARD_LIBRARIES} winmm.lib wsock32.lib oldnames.lib")
    SET(OSG_C_STANDARD_LIBRARIES "${CMAKE_C_STANDARD_LIBRARIES} winmm.lib wsock32.lib oldnames.lib")

    SET(OSG_CLEAR_STD_LIBS winspool.lib shell32.lib ole32.lib oleaut32.lib
                           uuid.lib comdlg32.lib msvcprt.lib msvcrt.lib)

    FOREACH(STD_LIB ${OSG_CLEAR_STD_LIBS})
        STRING(REPLACE ${STD_LIB} "" OSG_CXX_STANDARD_LIBRARIES ${OSG_CXX_STANDARD_LIBRARIES})
        STRING(REPLACE ${STD_LIB} "" OSG_C_STANDARD_LIBRARIES   ${OSG_C_STANDARD_LIBRARIES})
    ENDFOREACH()

    SET(CMAKE_CXX_STANDARD_LIBRARIES ${OSG_CXX_STANDARD_LIBRARIES} 
                                     CACHE STRING "OpenSG defaults" FORCE )
    SET(CMAKE_C_STANDARD_LIBRARIES   ${OSG_C_STANDARD_LIBRARIES} 
                                     CACHE STRING "OpenSG defaults" FORCE )

#    SET(CMAKE_CONFIGURATION_TYPES "Debug;Release;MinSizeRel;RelWithDebInfo;DebugRT" 
#                                  CACHE STRING "OpenSG Build Types" FORCE )

    SET(CMAKE_CONFIGURATION_TYPES "Debug;Release;DebugOpt;ReleaseNoOpt" 
                                  CACHE STRING "OpenSG Build Types" FORCE )



    # Shared Linker Flags

    SET(CMAKE_SHARED_LINKER_FLAGS_RELEASENOOPT 
        "${CMAKE_SHARED_LINKER_FLAGS_DEBUG} msvcprt.lib msvcrt.lib"
        CACHE STRING "OpenSG defaults" FORCE )

    SET(CMAKE_SHARED_LINKER_FLAGS_DEBUGOPT 
        "${CMAKE_SHARED_LINKER_FLAGS_RELEASE} /debug msvcprtd.lib msvcrtd.lib"
        CACHE STRING "OpenSG defaults" FORCE )

    SET(CMAKE_SHARED_LINKER_FLAGS_RELEASE 
        "${CMAKE_SHARED_LINKER_FLAGS_RELEASE} /debug msvcprt.lib msvcrt.lib"
        CACHE STRING "OpenSG defaults" FORCE )

    SET(CMAKE_SHARED_LINKER_FLAGS_MINSIZEREL 
        "${CMAKE_SHARED_LINKER_FLAGS_MINSIZEREL} msvcprt.lib msvcrt.lib"
        CACHE INTERNAL "OpenSG defaults" FORCE )

    SET(CMAKE_SHARED_LINKER_FLAGS_RELWITHDEBINFO 
        "${CMAKE_SHARED_LINKER_FLAGS_RELWITHDEBINFO} msvcprt.lib msvcrt.lib"
        CACHE INTERNAL "OpenSG defaults" FORCE )
    
    STRING(REPLACE "INCREMENTAL:YES" "INCREMENTAL:NO" replacementFlags ${CMAKE_SHARED_LINKER_FLAGS_DEBUG})
    SET(CMAKE_SHARED_LINKER_FLAGS_DEBUG "/INCREMENTAL:NO ${replacementFlags}" )
    
    SET(CMAKE_SHARED_LINKER_FLAGS_DEBUG 
        "${CMAKE_SHARED_LINKER_FLAGS_DEBUG} msvcprtd.lib msvcrtd.lib"
        CACHE STRING "OpenSG defaults" FORCE )



    SET(CMAKE_EXE_LINKER_FLAGS_RELEASENOOPT 
        "${CMAKE_EXE_LINKER_FLAGS_DEBUG} msvcprt.lib msvcrt.lib"
        CACHE STRING "OpenSG defaults" FORCE )

    SET(CMAKE_EXE_LINKER_FLAGS_DEBUG 
        "${CMAKE_EXE_LINKER_FLAGS_DEBUG} msvcprtd.lib msvcrtd.lib"
        CACHE STRING "OpenSG defaults" FORCE )

    SET(CMAKE_EXE_LINKER_FLAGS_DEBUGOPT 
        "${CMAKE_EXE_LINKER_FLAGS_RELEASE} /debug msvcprtd.lib msvcrtd.lib"
        CACHE STRING "OpenSG defaults" FORCE )

    SET(CMAKE_EXE_LINKER_FLAGS_RELEASE 
        "${CMAKE_EXE_LINKER_FLAGS_RELEASE} /debug msvcprt.lib msvcrt.lib"
        CACHE STRING "OpenSG defaults" FORCE )


    SET(CMAKE_EXE_LINKER_FLAGS_MINSIZEREL 
        "${CMAKE_EXE_LINKER_FLAGS_MINSIZEREL} msvcprt.lib msvcrt.lib"
        CACHE INTERNAL "OpenSG defaults" FORCE )

    SET(CMAKE_EXE_LINKER_FLAGS_RELWITHDEBINFO 
        "${CMAKE_EXE_LINKER_FLAGS_RELWITHDEBINFO} msvcprt.lib msvcrt.lib"
        CACHE INTERNAL "OpenSG defaults" FORCE )


    # Hide unused vars

    SET(CMAKE_MODULE_LINKER_FLAGS 
        "${CMAKE_MODULE_LINKER_FLAGS}"
        CACHE INTERNAL "OpenSG defaults" FORCE )

    SET(CMAKE_MODULE_LINKER_FLAGS_DEBUG 
        "${CMAKE_MODULE_LINKER_FLAGS_DEBUG}"
        CACHE INTERNAL "OpenSG defaults" FORCE )

    SET(CMAKE_MODULE_LINKER_FLAGS_MINSIZEREL 
        "${CMAKE_MODULE_LINKER_FLAGS_MINSIZEREL}"
        CACHE INTERNAL "OpenSG defaults" FORCE )

    SET(CMAKE_MODULE_LINKER_FLAGS_RELEASE 
        "${CMAKE_MODULE_LINKER_FLAGS_RELEASE}"
        CACHE INTERNAL "OpenSG defaults" FORCE )

    SET(CMAKE_MODULE_LINKER_FLAGS_RELWITHDEBINFO 
        "${CMAKE_MODULE_LINKER_FLAGS_RELWITHDEBINFO}"
        CACHE INTERNAL "OpenSG defaults" FORCE )


ENDIF(MSVC)

IF(CMAKE_COMPILER_IS_GNUCC)

    EXECUTE_PROCESS(COMMAND ${CMAKE_C_COMPILER} -dumpversion
                    OUTPUT_VARIABLE GCC_VERSION)
    SET(OSG_GCC_VERSION ${GCC_VERSION} CACHE STRING "" FORCE)

    MESSAGE("GOT gcc ${GCC_VERSION}")

    IF(OSG_PLATFORM_64 AND LINUX)
        SET(OSG_CXX_FLAGS "${OSG_CXX_FLAGS} -m64")
        SET(OSG_C_FLAGS   "${OSG_C_FLAGS} -m64")

        SET(OSG_EXE_LINKER_FLAGS    "${OSG_EXE_LINKER_FLAGS} -m64")
        SET(OSG_SHARED_LINKER_FLAGS "${OSG_SHARED_LINKER_FLAGS} -m64")

    ENDIF(OSG_PLATFORM_64 AND LINUX)

    SET(OSG_CXX_FLAGS "${OSG_CXX_FLAGS} -D__STDC_FORMAT_MACROS -fPIC")
    SET(OSG_C_FLAGS   "${OSG_C_FLAGS} -D__STDC_FORMAT_MACROS -fPIC")

    IF(OSG_ENABLE_C++11)
      IF(${GCC_VERSION} VERSION_LESS "4.7")
        SET(OSG_CXX_FLAGS "${OSG_CXX_FLAGS} -std=c++0x")
      ELSE()
        SET(OSG_CXX_FLAGS "${OSG_CXX_FLAGS} -std=c++11")
      ENDIF()
    ENDIF()
ENDIF(CMAKE_COMPILER_IS_GNUCC)


IF(APPLE AND NOT IOS)
  IF(OSG_ENABLE_C++11)
#    SET(OSG_CXX_FLAGS "${OSG_CXX_FLAGS} -std=c++11 -stdlib=libstdc++")
    SET(OSG_CXX_FLAGS "${OSG_CXX_FLAGS} -std=c++11 -stdlib=libc++ -Wno-deprecatd-register")
#    SET(OSG_CXX_FLAGS "${OSG_CXX_FLAGS} -std=c++11")
  ENDIF()
ENDIF()



SET(CMAKE_CXX_FLAGS         ${OSG_CXX_FLAGS} 
                            CACHE STRING "OpenSG defaults" FORCE )
SET(CMAKE_C_FLAGS           ${OSG_C_FLAGS} 
                            CACHE STRING "OpenSG defaults" FORCE )

SET(CMAKE_CXX_FLAGS_DEBUG   ${OSG_CXX_FLAGS_DEBUG} 
                            CACHE STRING "OpenSG defaults" FORCE )
SET(CMAKE_C_FLAGS_DEBUG     ${OSG_C_FLAGS_DEBUG} 
                            CACHE STRING "OpenSG defaults" FORCE )

SET(CMAKE_CXX_FLAGS_RELEASE ${OSG_CXX_FLAGS_RELEASE} 
                            CACHE STRING "OpenSG defaults" FORCE )
SET(CMAKE_C_FLAGS_RELEASE   ${OSG_C_FLAGS_RELEASE} 
                            CACHE STRING "OpenSG defaults" FORCE )


SET(CMAKE_EXE_LINKER_FLAGS    ${OSG_EXE_LINKER_FLAGS} 
                              CACHE STRING "OpenSG defaults" FORCE )
SET(CMAKE_SHARED_LINKER_FLAGS ${OSG_SHARED_LINKER_FLAGS} 
                              CACHE STRING "OpenSG defaults" FORCE )

   

###########
# GV stuff
###########

IF(CMAKE_COMPILER_IS_GNUCC)
#    SET(OSG_CXX_FLAGS_GV " -Wall -Wextra -Wreturn-type -Wold-style-cast -DOSG_DEBUG_OLD_C_CASTS -DOSG_CLEAN_FCFIELDS -DOSG_CHECK_CONST_CORRECT_FIELD_USAGE -Wwrite-strings -Werror -Wno-unused-parameter")

    SET(OSG_CXX_FLAGS_GV " -Wall -Wreturn-type -Wold-style-cast -DOSG_DEBUG_OLD_C_CASTS -DOSG_CLEAN_FCFIELDS -DOSG_CHECK_CONST_CORRECT_FIELD_USAGE -Wwrite-strings -Werror -Wno-unused-parameter")

#    SET(OSG_C_FLAGS_GV " -Wall -Wextra -Wreturn-type -Wold-style-cast -DOSG_DEBUG_OLD_C_CASTS -DOSG_CLEAN_FCFIELDS -DOSG_CHECK_CONST_CORRECT_FIELD_USAGE -Wwrite-strings -Werror -Wno-unused-parameter")
    SET(OSG_C_FLAGS_GV " -Wall -Wextra -Wreturn-type -Wold-style-cast -DOSG_DEBUG_OLD_C_CASTS -DOSG_CLEAN_FCFIELDS -DOSG_CHECK_CONST_CORRECT_FIELD_USAGE -Wwrite-strings -Werror -Wno-unused-parameter")


    SET(OSG_ADD_CXX_FLAGS_GV "")
    SET(OSG_ADD_C_FLAGS_GV "")

    SET(OSG_SHARED_LINKER_FLAGS_GV " -Wl,--no-undefined")


##########
# Debug
##########

    SET(CMAKE_CXX_FLAGS_DEBUGGV 
        "${CMAKE_CXX_FLAGS_DEBUG}${OSG_CXX_FLAGS_GV}" 
        CACHE STRING "Flags used by the C++ compiler during maintainer builds."
        FORCE)

    SET(CMAKE_C_FLAGS_DEBUGGV 
        "${CMAKE_C_FLAGS_DEBUG}${OSG_C_FLAGS_GV}" 
        CACHE STRING "Flags used by the C compiler during maintainer builds."
        FORCE)

    SET(CMAKE_EXE_LINKER_FLAGS_DEBUGGV
        "${CMAKE_EXE_LINKER_FLAGS_DEBUG}" 
        CACHE STRING "Flags used for linking binaries during maintainer builds."
        FORCE)

    SET(CMAKE_MODULE_LINKER_FLAGS_DEBUGGV
        "${CMAKE_MODULE_LINKER_FLAGS_DEBUG}" 
        CACHE STRING "Flags used for linking binaries during maintainer builds."
        FORCE)

    SET(CMAKE_SHARED_LINKER_FLAGS_DEBUGGV
        "${CMAKE_SHARED_LINKER_FLAGS_DEBUG}${OSG_SHARED_LINKER_FLAGS_GV}" 
        CACHE STRING
        "Flags used by the shared libraries linker during maintainer builds."
        FORCE)

    ##########
    # Release
    ##########

    SET(CMAKE_CXX_FLAGS_RELEASEGV 
        "${CMAKE_CXX_FLAGS_RELEASE}${OSG_CXX_FLAGS_GV}" 
        CACHE STRING "Flags used by the C++ compiler during gv builds."
        FORCE)

    SET(CMAKE_C_FLAGS_RELEASEGV 
        "${CMAKE_C_FLAGS_RELEASE}${OSG_C_FLAGS_GV}"
        CACHE STRING "Flags used by the C compiler during gv builds."
        FORCE)

    SET(CMAKE_EXE_LINKER_FLAGS_RELEASEGV
        "${CMAKE_EXE_LINKER_FLAGS_RELEASE}" 
        CACHE STRING "Flags used for linking binaries during gv builds."
        FORCE)

    SET(CMAKE_MODULE_LINKER_FLAGS_RELEASEGV
         "${CMAKE_MODULE_LINKER_FLAGS_RELEASE}" 
        CACHE STRING "Flags used for linking binaries during gv builds."
        FORCE)

    SET(CMAKE_SHARED_LINKER_FLAGS_RELEASEGV
        "${CMAKE_SHARED_LINKER_FLAGS_RELEASE}${OSG_SHARED_LINKER_FLAGS_GV}" 
        CACHE STRING
        "Flags used by the shared libraries linker during gv builds."
        FORCE)

ENDIF(CMAKE_COMPILER_IS_GNUCC)
