AC_DEFUN(AC_GDZ_PROG_CXX_WORKS,
[AC_BEFORE([$0], [AC_PROG_CXXCPP])dnl

if test $2"set" = set; then
    AC_PATH_PROGS(CXX, $1, unknown_compiler, $PATH)
else
    AC_PATH_PROGS(CXX, $1, unknown_compiler, $PATH:$2)
fi

AC_PROG_CXX_WORKS
AC_PROG_CXX_GNU

dnl Check whether -g works, even if CXXFLAGS is set, in case the package
dnl plays around with CXXFLAGS (such as to build both debugging and
dnl normal versions of a library), tasteless as that idea is.
ac_test_CXXFLAGS="${CXXFLAGS+set}"
ac_save_CXXFLAGS="$CXXFLAGS"
CXXFLAGS=
AC_PROG_CXX_G
if test "$ac_test_CXXFLAGS" = set; then
  CXXFLAGS="$ac_save_CXXFLAGS"
elif test $ac_cv_prog_cxx_g = yes; then
  if test "$GXX" = yes; then
    CXXFLAGS="-g -O2"
  else
    CXXFLAGS="-g"
  fi
else
  if test "$GXX" = yes; then
    CXXFLAGS="-O2"
  else
    CXXFLAGS=
  fi
fi
])
AC_DEFUN(AC_GDZ_PROG_CXX_AVAILABLE,
[AC_BEFORE([$0], [AC_PROG_CXXCPP])dnl

if test "$2set" = set; then
    AC_PATH_PROGS(CXX, $1, unknown_compiler, $PATH)
else
    AC_PATH_PROGS(CXX, $1, unknown_compiler, $PATH:$2)
fi

AC_PROG_CXX_GNU

dnl Check whether -g works, even if CXXFLAGS is set, in case the package
dnl plays around with CXXFLAGS (such as to build both debugging and
dnl normal versions of a library), tasteless as that idea is.
ac_test_CXXFLAGS="${CXXFLAGS+set}"
ac_save_CXXFLAGS="$CXXFLAGS"
CXXFLAGS=
AC_PROG_CXX_G
if test "$ac_test_CXXFLAGS" = set; then
  CXXFLAGS="$ac_save_CXXFLAGS"
elif test $ac_cv_prog_cxx_g = yes; then
  if test "$GXX" = yes; then
    CXXFLAGS="-g -O2"
  else
    CXXFLAGS="-g"
  fi
else
  if test "$GXX" = yes; then
    CXXFLAGS="-O2"
  else
    CXXFLAGS=
  fi
fi
])

AC_DEFUN(AC_GDZ_PROG_CC_WORKS,
[AC_MSG_CHECKING([whether the C compiler ($CC $CFLAGS $LDFLAGS) works])
AC_LANG_SAVE
AC_LANG_C

if test "set"$2 = set; then
    AC_PATH_PROGS(CC, $1, unknown_compiler, $PATH)
else
    AC_PATH_PROGS(CC, $1, unknown_compiler, $PATH:$2)
fi

AC_TRY_COMPILER([main(){return(0);}], ac_cv_prog_cc_works, ac_cv_prog_cc_cross)
AC_LANG_RESTORE
AC_MSG_RESULT($ac_cv_prog_cc_works)
if test $ac_cv_prog_cc_works = no; then
  AC_MSG_ERROR([installation or configuration problem: C compiler cannot create executables.])
fi
AC_MSG_CHECKING([whether the C compiler ($CC $CFLAGS $LDFLAGS) is a cross-compiler])
AC_MSG_RESULT($ac_cv_prog_cc_cross)
cross_compiling=$ac_cv_prog_cc_cross
])

AC_DEFUN(AC_GDZ_PROG_CC_AVAILABLE,
[AC_MSG_CHECKING([whether the C compiler ($CC $CFLAGS $LDFLAGS) works])

AC_LANG_SAVE
AC_LANG_C

if [[ "xset$2" = xset ]]; then
    AC_PATH_PROGS(CC, $1, unknown_compiler, $PATH)
else
    AC_PATH_PROGS(CC, $1, unknown_compiler, $PATH:$2)
fi


AC_LANG_RESTORE

AC_MSG_RESULT($ac_cv_prog_cc_works)

cross_compiling=$ac_cv_prog_cc_cross
])

AC_DEFUN(AC_GDZ_FIND_PROG_DIR,
[
    ac_gdz_find_prog_dir_result=""

    test_path=$1

    for drive in c d e f g; do
        for progdir in "Program Files/" "Programme/" ""; do
            if test -d "//$drive/${progdir}${test_path}"; then
                ac_gdz_find_prog_dir_result="//$drive/${progdir}${test_path}"
                break 2
            fi
        done
    done
])

AC_DEFUN(AC_GDZ_SETUP_INTEL,
[
    changequote(<<, >>)dnl

    ac_gdz_compiler_version=`echo $ac_gdz_compiler | sed 's/^\(icl\)\([0-9]*\)$/\2/'`
    ac_gdz_compiler_base=icl

    changequote([, ])dnl

    if test $ac_gdz_compiler_version"set" = set; then
        ac_gdz_compiler_version=50
    fi

    case $ac_gdz_compiler_version in

        50)
        ac_gdz_intelsearchdir=Intel/compiler$ac_gdz_compiler_version/ia32
        ;;
        45)
        ac_gdz_intelsearchdir=Intel/compiler$ac_gdz_compiler_version
        ;;
         *)
        ac_gdz_intelsearchdir=Intel/compiler$ac_gdz_compiler_version
        ;;
    esac    

    AC_GDZ_FIND_PROG_DIR($ac_gdz_intelsearchdir)

    ac_gdz_compiler_dir=$ac_gdz_find_prog_dir_result
    ac_gdz_compiler_path=$ac_gdz_compiler_dir/bin
    ac_gdz_compiler_incl=$ac_gdz_compiler_dir/Include
    ac_gdz_compiler_lib=$ac_gdz_compiler_dir/Lib
    ac_gdz_compiler_exe=icl.exe
    ac_gdz_linker_exe=xilink.exe
    ac_gdz_check_compiler_available=yes
])

AC_DEFUN(AC_GDZ_SETUP_BORLAND,
[
    changequote(<<, >>)dnl

    ac_gdz_compiler_version=`echo $ac_gdz_compiler | sed 's/^\(bcc\)\([0-9]*\)$/\2/'`
    ac_gdz_compiler_base=bcc

    changequote([, ])dnl

    if test $ac_gdz_compiler_version"set" = set; then
        ac_gdz_compiler_version=55
    fi

    case $ac_gdz_compiler_version in

        55)
        ac_gdz_borlandsearchdir=Borland/BCC$ac_gdz_compiler_version
        ;;
        *)
        ac_gdz_borlandsearchdir=Borland/BCC$ac_gdz_compiler_version
        ;;
    esac    

    AC_GDZ_FIND_PROG_DIR($ac_gdz_borlandsearchdir)

    ac_gdz_compiler_dir=$ac_gdz_find_prog_dir_result
    ac_gdz_compiler_path=$ac_gdz_compiler_dir/bin
    ac_gdz_compiler_incl=$ac_gdz_compiler_dir/Include
    ac_gdz_compiler_lib=$ac_gdz_compiler_dir/Lib
    ac_gdz_compiler_exe=bcc32.exe
    ac_gdz_linker_exe=bcc32.exe
    ac_gdz_check_compiler_available=yes
])

AC_DEFUN(AC_GDZ_GET_MSVS_PATH,
[
])

AC_DEFUN(AC_GDZ_GUESS_COMPILER_DIR_AND_EXE,
[
    AC_MSG_CHECKING("/ guessing compiler dir for $build-$ac_gdz_compiler")

    case "$build_os" in
       irix*)
        ac_gdz_compiler_exe=$ac_gdz_compiler
        ac_gdz_compiler_path=/usr/bin
        ;;
        *-pc-linux-gnu)
        ac_gdz_compiler_exe=$ac_gdz_compiler
        ac_gdz_compiler_path=/usr/bin
        ;;
       cygwin*)

        case "$ac_gdz_compiler" in
            icl*)
            AC_GDZ_SETUP_INTEL()
            ;;
            bcc*)
            AC_GDZ_SETUP_BORLAND()
            ;;
        esac

        ;;
        *)
        ;;
    esac

    AC_MSG_RESULT($ac_gdz_compiler_path)
])

AC_DEFUN(AC_GDZ_GUESS_COMPILER_DEFAULTS,
[
    # guess compiler if not set
    if test "x$ac_gdz_compiler" == "x"
    then
        case "$build_os" in
        cygwin*)    ac_gdz_compiler=icl50 
                    ;;
        linux*)     ac_gdz_compiler=g++
                    ;;
        irix*)      ac_gdz_compiler=CC
                    ;;
        *)          echo "System $build_os unknown, use --with-compiler!"
                    exit 1
                    ;;
        esac
        echo "selected compiler $ac_gdz_compiler for system $build_os"
    fi
])

AC_DEFUN(AC_GDZ_SET_COMPILER_DEFAULTS,
[
    ac_gdz_check_compiler_available=no

    AC_MSG_CHECKING("site config conf.$build-$ac_gdz_compiler.in")

    if test -r "$ac_gdz_commonconf_dir/conf.$build-$ac_gdz_compiler.in"; then
        AC_MSG_RESULT("yes")
        . "$ac_gdz_commonconf_dir/conf.$build-$ac_gdz_compiler.in"
    else
        AC_MSG_RESULT("no")
    fi

    if test $ac_gdz_compiler_dir"set" = set; then 
        AC_GDZ_GUESS_COMPILER_DIR_AND_EXE()
    fi

    if test $ac_gdz_check_compiler_available = yes; then
        AC_GDZ_PROG_CC_AVAILABLE($ac_gdz_c_compiler_exe, $ac_gdz_compiler_path)
        AC_GDZ_PROG_CXX_AVAILABLE($ac_gdz_compiler_exe, $ac_gdz_compiler_path)
    else
        AC_GDZ_PROG_CC_WORKS($ac_gdz_c_compiler_exe, $ac_gdz_compiler_path)
        AC_GDZ_PROG_CXX_WORKS($ac_gdz_compiler_exe, $ac_gdz_compiler_path)
        ac_gdz_compiler_exe=$CXX
    fi
])

AC_DEFUN(AC_GDZ_EXEEXT, 
[
    case "$build_os" in

       cygwin*)
        AC_MSG_CHECKING(executable suffix)
        EXEEXT=.exe
        ac_gdz_exe_suffix=.exe
        AC_MSG_RESULT($EXEEXT)
        ;;

        *)
        AC_EXEEXT()
        ac_gdz_exe_suffix=.$EXEEXT
        ;;

    esac

    if [[ $ac_gdz_exe_suffix = "." ]]; then
        ac_gdz_exe_suffix=
    fi
])

AC_DEFUN(AC_GDZ_OBJEXT,
[
    case "$build_os" in

       cygwin*)
        if [[ $ac_gdz_compiler_base = g++ ]]; then
        	AC_MSG_CHECKING(obj suffix)
        	ac_gdz_obj_suffix=.o
        	AC_MSG_RESULT($ac_gdz_obj_suffix)
        else
        	AC_MSG_CHECKING(obj suffix)
        	ac_gdz_obj_suffix=.obj
        	AC_MSG_RESULT($ac_gdz_obj_suffix)
        fi
        ;;

        *)
        AC_OBJEXT()
        ac_gdz_obj_suffix=.$OBJEXT
        ;;

    esac
])

AC_DEFUN(AC_GDZ_LIBEXT,
[
    AC_MSG_CHECKING(lib suffix)

    case "$build_os" in

       cygwin*)
        if [[ $ac_gdz_compiler_base = g++ ]]; then
	        ac_gdz_lib_suffix=.a
        else
	        ac_gdz_lib_suffix=.lib
	    fi
        ;;

        *)
        ac_gdz_lib_suffix=.a
        ;;

    esac

    AC_MSG_RESULT($ac_gdz_lib_suffix)
])

AC_DEFUN(AC_GDZ_SOEXT,
[
    AC_MSG_CHECKING(shared object suffix)

    case "$build_os" in

       cygwin*)
        ac_gdz_so_suffix=.dll
        ;;

        *)
        ac_gdz_so_suffix=.so
        ;;

    esac

    AC_MSG_RESULT($ac_gdz_so_suffix)
])

AC_DEFUN(AC_GDZ_SOPRAEFIX,
[
     AC_MSG_CHECKING(shared object praefix)

     case "$build_os" in

       cygwin*)
        ac_gdz_so_praefix=
        ;;

        *)
        ac_gdz_so_praefix=lib
        ;;

    esac

    AC_MSG_RESULT($ac_gdz_so_praefix)
])

AC_DEFUN(AC_GDZ_FIND_STUDIO_DIR,
[
    ac_gdz_find_prog_dir_result=""

    for drive in c d e f g; do
     for progdir in "Program Files" "Programme"; do
      if test -d "//$drive/$progdir/Microsoft Visual Studio"; then
       ac_gdz_find_prog_dir_result="//$drive/$progdir/Microsoft Visual Studio"
       break 2
      fi
     done
    done
])

AC_DEFUN(AC_GDZ_SET_SYSTEM_DIRS,
[
    AC_MSG_CHECKING(system dir)

    case "$build_os" in
        cygwin*)
            case "$ac_gdz_compiler" in
                icl*)
                    AC_GDZ_FIND_STUDIO_DIR()

                    ac_gdz_studio_dir=$ac_gdz_find_prog_dir_result

                    ac_gdz_system_incl_dir=$ac_gdz_studio_dir/VC98/Include
                    ac_gdz_system_lib_dir=$ac_gdz_studio_dir/VC98/Lib
                ;;
                *)
                    ac_gdz_system_incl_dir=$ac_gdz_compiler_incl
                    ac_gdz_system_lib_dir=$ac_gdz_compiler_lib
                ;;
            esac
        ;;

        *)
        ac_gdz_so_praefix=lib
        ;;
    esac

    AC_MSG_RESULT($ac_gdz_studio_dir)
])

AC_DEFUN(AC_GDZ_SCAN_PACKET_DESC,
[
    changequote(<<, >>)dnl

    let i=0

    until [[ $i = ${#ac_gdz_package[*]} ]]; do

        p1=`echo ${ac_gdz_package[$i]} | sed 's/\([^:]*\):\([^:]*\):\([^:]*\):\([^:]*\):\([^:]*\):\([^:]*\):\([^:]*\)/\1/'`
        p1=`echo $p1 | sed 's/://g'`

        p2=`echo ${ac_gdz_package[$i]} | sed 's/\([^:]*\):\([^:]*\):\([^:]*\):\([^:]*\):\([^:]*\):\([^:]*\):\([^:]*\)/\2/'`
        p2=`echo $p2 | sed 's/://g'`

        p3=`echo ${ac_gdz_package[$i]} | sed 's/\([^:]*\):\([^:]*\):\([^:]*\):\([^:]*\):\([^:]*\):\([^:]*\):\([^:]*\)/\3/'`
        p3=`echo $p3 | sed 's/://g'`

        p4=`echo ${ac_gdz_package[$i]} | sed 's/\([^:]*\):\([^:]*\):\([^:]*\):\([^:]*\):\([^:]*\):\([^:]*\):\([^:]*\)/\4/'`
        p4=`echo $p4 | sed 's/://g'`

        p5=`echo ${ac_gdz_package[$i]} | sed 's/\([^:]*\):\([^:]*\):\([^:]*\):\([^:]*\):\([^:]*\):\([^:]*\):\([^:]*\)/\5/'`
        p5=`echo $p5 | sed 's/://g'`

        p6=`echo ${ac_gdz_package[$i]} | sed 's/\([^:]*\):\([^:]*\):\([^:]*\):\([^:]*\):\([^:]*\):\([^:]*\):\([^:]*\)/\6/'`
        p6=`echo $p6 | sed 's/://g'`

        p7=`echo ${ac_gdz_package[$i]} | sed 's/\([^:]*\):\([^:]*\):\([^:]*\):\([^:]*\):\([^:]*\):\([^:]*\):\([^:]*\)/\7/'`
        p7=`echo $p7 | sed 's/://g'`
    
        if [[ ${build_os} = "cygwin" ]]; then
            p4=`echo $p4 | sed 's/@WINDOWSYSTEM@/WIN32/g'`
            p5=`echo $p5 | sed 's/@WINDOWSYSTEM@/WIN32/g'`
        else
            p4=`echo $p4 | sed 's/@WINDOWSYSTEM@/X/g'`
            p5=`echo $p5 | sed 's/@WINDOWSYSTEM@/X/g'`
        fi

        ac_gdz_package_name[$i]=$p1;
        ac_gdz_package_fact_init[$i]=$p2
        ac_gdz_package_dirs[$i]=$p3;
        ac_gdz_package_inc_dep[$i]=$p4;
        ac_gdz_package_link_dep[$i]=$p5;
        ac_gdz_package_testinc_dep[$i]=$p6;
        ac_gdz_package_testlink_dep[$i]=$p7;

        let i=i+1
    done

    changequote([, ])dnl
])


AC_DEFUN(AC_GDZ_WRITE_PACKET_MAKE,
[

dnl e2

    let i=0

    changequote(<<, >>)dnl

    until [[ $i = ${#ac_gdz_package[*]} ]]; do

        echo configuring package $i ${ac_gdz_package_name[$i]}

        if [[ ${ac_gdz_package_name[$i]} = "WindowX" ]]; then
            if [[ ${build_os} = "cygwin" ]]; then
                echo Skipping ${ac_gdz_package_name[$i]}
                let i=i+1
                continue
            else
                ac_gdz_package_order="${ac_gdz_package_order} WindowXLib"
            fi
        fi
        if [[ ${ac_gdz_package_name[$i]} = "WindowWIN32" ]]; then
            if [[ ${build_os} != "cygwin" ]]; then
                echo Skipping ${ac_gdz_package_name[$i]}
                let i=i+1
                continue
            else
                ac_gdz_package_order="${ac_gdz_package_order} WindowWIN32Lib"
            fi
        fi
        if [[ ${ac_gdz_package_name[$i]} = "WindowQT" ]]; then
            if [[ ${ac_gdz_conf_package_qt} = 0 ]]; then
                echo Skipping ${ac_gdz_package_name[$i]}
                let i=i+1
                continue
            else
                ac_gdz_package_order="${ac_gdz_package_order} WindowQTLib"
            fi
        fi
        if [[ ${ac_gdz_package_name[$i]} = "WindowGLUT" ]]; then
            if [[ ${ac_gdz_conf_package_glut} = 0 ]]; then
                echo Skipping ${ac_gdz_package_name[$i]}
                let i=i+1
                continue
            else
                ac_gdz_package_order="${ac_gdz_package_order} WindowGLUTLib"
            fi
        fi


        ac_gdz_package_name_out=${ac_gdz_package_name[$i]}

        ac_gdz_package_inc_dep_out=${ac_gdz_package_inc_dep[$i]}
        ac_gdz_package_inc_dep_out_files= 

        ac_gdz_package_link_dep_out=${ac_gdz_package_link_dep[$i]}

        for dir in ${ac_gdz_package_inc_dep[$i]}; do

            ac_gdz_package_check_dir_e2=$ac_gdz_src_dir/$dir

            if [[ -d $ac_gdz_package_check_dir_e2 ]]; then
                ac_gdz_package_inc_dep_out_files=$ac_gdz_package_inc_dep_out_files' $('${ac_gdz_project_praefix}'POOL)'/$dir/common.mk
            else
                ac_gdz_package_check_file_e2=$ac_gdz_commonpackage_dir/common$dir.mk

                if [[ -r $ac_gdz_package_check_file_e2 ]]; then
                    ac_gdz_package_inc_dep_out_files="$ac_gdz_package_inc_dep_out_files $ac_gdz_commonpackage_dir/common$dir.mk"
    
                    if [[ $build_os = cygwin ]]; then
                        ac_gdz_package_link_dep_out="$ac_gdz_package_link_dep_out $dir"
                    fi
                else
                    ac_gdz_package_inc_dep_out_files=$ac_gdz_package_inc_dep_out_files' $('${ac_gdz_project_praefix}'POOL)'/$dir/common.mk
                fi
            fi
        done

        ac_gdz_package_link_dep_out_files=

        for dir in ${ac_gdz_package_link_dep[$i]}; do
            ac_gdz_package_check_file_e2=$ac_gdz_commonpackage_dir/common$dir.mk
            
            if [[ -r $ac_gdz_package_check_file_e2 ]]; then
                ac_gdz_package_link_dep_out_files="$ac_gdz_package_link_dep_out_files $ac_gdz_commonpackage_dir/common$dir.mk"
            else
                ac_gdz_package_link_dep_out_files=$ac_gdz_package_link_dep_out_files' $(BUILD_BASE)'/$dir/common.mk
            fi
        done

        ac_gdz_package_testinc_dep_out=${ac_gdz_package_name_out}Lib' '${ac_gdz_package_testinc_dep[$i]}
        ac_gdz_package_testinc_dep_out_files='$(BUILD_BASE)'/${ac_gdz_package_name_out}Lib/common.mk

        for dir in ${ac_gdz_package_testinc_dep[$i]}; do
            ac_gdz_package_check_file_e2=$ac_gdz_src_dir/$dir/common.mk
            
            if [[ -r $ac_gdz_package_check_file_e2 ]]; then
                ac_gdz_package_testinc_dep_out_files="$ac_gdz_package_testinc_dep_out_files $ac_gdz_src_dir/$dir/common.mk"
            else
                ac_gdz_package_testinc_dep_out_files=$ac_gdz_package_testinc_dep_out_files' $(BUILD_BASE)'/$dir/common.mk
            fi
        done


        ac_gdz_package_testlink_dep_out=${ac_gdz_package_name_out}Lib' '${ac_gdz_package_testlink_dep[$i]}
dnl        ac_gdz_package_testlink_dep_out_files=$ac_gdz_package_link_dep_out_files' $(BUILD_BASE)'/${ac_gdz_package_name_out}Lib/common.mk
        ac_gdz_package_testlink_dep_out_files='$(BUILD_BASE)'/${ac_gdz_package_name_out}Lib/common.mk

        for dir in ${ac_gdz_package_testlink_dep[$i]}; do
            ac_gdz_package_check_file_e2=$ac_gdz_commonpackage_dir/common$dir.mk
            
            if [[ -r $ac_gdz_package_check_file_e2 ]]; then
                ac_gdz_package_testlink_dep_out_files="$ac_gdz_package_testlink_dep_out_files $ac_gdz_commonpackage_dir/common$dir.mk"
            else
                ac_gdz_package_testlink_dep_out_files=$ac_gdz_package_testlink_dep_out_files' $(BUILD_BASE)'/$dir/common.mk
            fi
        done


        ac_gdz_package_dir_base=${ac_gdz_package_sub_dir_out}/${ac_gdz_package_name[$i]}
        ac_gdz_package_dir=${ac_gdz_package_dir_base}Lib
        ac_gdz_package_test_dir=${ac_gdz_package_dir_base}Test

        ac_gdz_common_packet_make=${ac_gdz_package_dir}/Makefile
        ac_gdz_common_packet_testmake=${ac_gdz_package_test_dir}/Makefile

        if [[ ${ac_gdz_package_fact_init[$i]} = "1" ]]; then
            if [[ $build_os = cygwin ]]; then
                ac_gdz_common_init_code_in_e2=${ac_gdz_commonconf_dir}/OSGDllInit.cpp.in
                ac_gdz_common_init_code_e2=${ac_gdz_package_dir}/OSGDllInit.cpp
                ac_gdz_common_init_code_files_e2="$ac_gdz_common_init_code_e2:$ac_gdz_common_init_code_in_e2"
                ac_gdz_package_so_needs_init_e2=1
            elif [[ $build_os = linux-gnu ]]; then
                ac_gdz_common_init_code_in_e2=${ac_gdz_commonconf_dir}/OSGSoInit.cpp.in
                ac_gdz_common_init_code_e2=${ac_gdz_package_dir}/OSGSoInit.cpp
                ac_gdz_common_init_code_files_e2="$ac_gdz_common_init_code_e2:$ac_gdz_common_init_code_in_e2"
                ac_gdz_package_so_needs_init_e2=0
            elif [[ $build_os = solaris2.7 ]]; then
                ac_gdz_common_init_code_i_e2=${ac_gdz_commonconf_dir}/OSGSoInit.cpp.in
                ac_gdz_common_init_code_e2=${ac_gdz_package_dir}/OSGSoInit.cpp
                ac_gdz_common_init_code_files_e2="$ac_gdz_common_init_code_e2:$ac_gdz_common_init_code_in_e2"
                ac_gdz_package_so_needs_init_e2=0
            else
                ac_gdz_common_init_code_in_e2=${ac_gdz_commonconf_dir}/OSGSoInit.cpp.in
                ac_gdz_common_init_code_e2=${ac_gdz_package_dir}/OSGSoInit.cpp
                ac_gdz_common_init_code_files_e2="$ac_gdz_common_init_code_e2:$ac_gdz_common_init_code_in_e2"
                ac_gdz_package_so_needs_init_e2=1
            fi
        else
            ac_gdz_common_init_code_files_e2=
            ac_gdz_package_so_needs_init_e2=0
        fi

        ac_gdz_common_mk_in_e2=${ac_gdz_commonconf_dir}/common.mk.in
        ac_gdz_common_mk_out_e2=${ac_gdz_package_dir}/common.mk
        ac_gdz_common_mk_files_e2="$ac_gdz_common_mk_out_e2:$ac_gdz_common_mk_in_e2"

        ac_gdz_vpath_out=.

        iFirstTime="yes"
        ac_gdz_package_def_e2=

        for dir in ${ac_gdz_package_dirs[$i]}; do

            p1=`echo ${dir} | sed 's/\([^@]*\)@\(.*\)/\1/'`
            p2=`echo ${dir} | sed 's/\([^@]*\)@\(.*\)/\2/'`
            
        	FK_GDZ_CREATE_PACKAGE_DIRS ${ac_gdz_package_dir_base}
        
            if [[ -n $p2 ]]; then
                if [[ $build_os = $p2 ]]; then
                    ac_gdz_vpath_out=$ac_gdz_vpath_out:'$('${ac_gdz_project_praefix}'POOL)'/$p1

                    ac_gdz_def_file=$p1/lib.def

                    echo "Check Def : $ac_gdz_def_file"

                    if [[ -r $ac_gdz_def_file ]]; then
                        if [[ $iFirstTime = "yes" ]]; then
                            ac_gdz_package_def_e2=lib.def
                            echo "    cp  ${ac_gdz_commonconf_dir}/lib${ac_gdz_package_name[$i]}.def.in ${ac_gdz_package_dir}/lib.def"
                            echo "    cat $ac_gdz_def_file >> ${ac_gdz_package_dir}/lib.def"
                            cp  ${ac_gdz_commonconf_dir}/lib${ac_gdz_package_name[$i]}.def.in ${ac_gdz_package_dir}/lib.def
                            cat $ac_gdz_def_file >> ${ac_gdz_package_dir}/lib.def
                            iFirstTime="no"
                        else
                            echo "    cat $ac_gdz_def_file >> ${ac_gdz_package_dir}/lib.def"
                            cat $ac_gdz_def_file >> ${ac_gdz_package_dir}/lib.def
                        fi
                    fi
                fi
            else
                ac_gdz_vpath_out=$ac_gdz_vpath_out:'$('${ac_gdz_project_praefix}'POOL)'/$p1

                ac_gdz_def_file=$p1/lib.def

                echo "Check Def : $ac_gdz_def_file"

                if [[ -r $ac_gdz_def_file ]]; then
                    if [[ $iFirstTime = "yes" ]]; then
                        ac_gdz_package_def_e2=lib.def
                        echo "    cp  ${ac_gdz_commonconf_dir}/lib${ac_gdz_package_name[$i]}.def.in ${ac_gdz_package_dir}/lib.def"
                        echo "    cat $ac_gdz_def_file >> ${ac_gdz_package_dir}/lib.def"
                        cp  ${ac_gdz_commonconf_dir}/lib${ac_gdz_package_name[$i]}.def.in ${ac_gdz_package_dir}/lib.def
                        cat $ac_gdz_def_file >> ${ac_gdz_package_dir}/lib.def
                        iFirstTime="no"
                    else
                        echo "    cat $ac_gdz_def_file >> ${ac_gdz_package_dir}/lib.def"
                        cat $ac_gdz_def_file >> ${ac_gdz_package_dir}/lib.def
                    fi
                fi
            fi
        done

        changequote([, ])dnl

        ac_gdz_win_pool_e2=
        ac_gdz_win_build_base_e2=
        ac_gdz_build_dir_e2=$ac_gdz_build_dir        

        ac_gdz_package_test_debug_libs_e2=$ac_gdz_test_debug_libs

        if [[ $build_os = cygwin ]]; then
            ac_gdz_src_dir_win_e2=`cygpath -w $ac_gdz_src_dir`
            ac_gdz_win_pool_e2=${ac_gdz_project_praefix}POOL_WIN"     ?= "$ac_gdz_src_dir_win_e2

            ac_gdz_package_sub_dir_win_e2=`cygpath -w $ac_gdz_build_dir_e2/$ac_gdz_package_sub_dir_out`
            ac_gdz_win_build_base_e2="BUILD_BASE_WIN := "$ac_gdz_package_sub_dir_win_e2
        fi

        AC_SUBST(ac_gdz_src_dir)
        AC_SUBST(ac_gdz_build_dir_e2)
        AC_SUBST(ac_gdz_win_pool_e2)
        AC_SUBST(ac_gdz_win_build_base_e2)
        AC_SUBST(ac_gdz_package_name_out)
        AC_SUBST(ac_gdz_package_inc_dep_out)
        AC_SUBST(ac_gdz_package_inc_dep_out_files)
        AC_SUBST(ac_gdz_package_link_dep_out)
        AC_SUBST(ac_gdz_package_link_dep_out_files)
        AC_SUBST(ac_gdz_package_testinc_dep_out)
        AC_SUBST(ac_gdz_package_testinc_dep_out_files)
        AC_SUBST(ac_gdz_package_testlink_dep_out)
        AC_SUBST(ac_gdz_package_testlink_dep_out_files)

        AC_SUBST(ac_gdz_package_sub_dir_out)        AC_SUBST(ac_gdz_package_sys_common_out)
        
        AC_SUBST(ac_gdz_vpath_out)
        AC_SUBST(ac_gdz_project_praefix)

        AC_SUBST(ac_gdz_package_so_needs_init_e2)

        AC_SUBST(ac_gdz_package_def_e2)

        AC_SUBST(ac_gdz_package_test_debug_libs_e2)        

        touch confdefs.h

        AC_OUTPUT([$ac_gdz_common_packet_make:$ac_gdz_common_packetmake_in
                   $ac_gdz_common_packet_testmake:$ac_gdz_common_testmake_in
                   $ac_gdz_common_init_code_files_e2 
                   $ac_gdz_common_mk_files_e2])

        let i=i+1
    done

])


AC_DEFUN(AC_GDZ_WRITE_BUILDS_MAKE,
[
dnl e3

    ac_gdz_common_builds_make_e3=$ac_gdz_package_sub_dir_out/Makefile
    ac_gdz_install_prefix_e3=$ac_gdz_install_prefix

    AC_SUBST(ac_gdz_lib_src_dir)
    AC_SUBST(ac_gdz_package_order)
    AC_SUBST(ac_gdz_lib_package_sys_common_out)
    AC_SUBST(ac_gdz_lib_project_praefix)
    AC_SUBST(ac_gdz_install_prefix_e3)

    touch confdefs.h

    AC_OUTPUT($ac_gdz_common_builds_make_e3:$ac_gdz_common_buildsmake_in)
])



AC_DEFUN(AC_GDZ_WRITE_COMMON_STL,
[
dnl e4

    ac_gdz_stl_lib_e4=
    ac_gdz_stl_dir_e4=

    if [[ -n "$ac_gdz_stl_dir" ]]; then
        ac_gdz_stl_lib_e4='-lCio'
        ac_gdz_stl_dir_e4=$ac_gdz_stl_dir
    else
        if [[ $build_os = irix6.5 ]]; then
            ac_gdz_stl_lib_e4='-lCio'
        fi
    fi

    ac_gdz_common_stl_in_e4=$ac_gdz_commonconf_dir/commonSTL.in
    ac_gdz_common_stl_e4=$ac_gdz_commonpackage_dir/commonSTL.mk

    AC_SUBST(ac_gdz_stl_dir_e4)
    AC_SUBST(ac_gdz_stl_lib_e4)
   
    touch confdefs.h

    AC_OUTPUT($ac_gdz_common_stl_e4:$ac_gdz_common_stl_in_e4)
])

AC_DEFUN(AC_GDZ_WRITE_COMMON_GLUT,
[
dnl e5

    ac_gdz_glut_lib_e5=
    ac_gdz_glut_incdir_e5=
    ac_gdz_glut_libdir_e5=

    if [[ "$with_glut" = yes ]]; then
        if [[ $build_os = cygwin ]]; then
           ac_gdz_glut_lib_e5='glut32.lib'
        else
           ac_gdz_glut_lib_e5='-lglut'
        fi
    elif [[ -n "$ac_gdz_glut_dir" ]]; then
        if [[ $build_os = cygwin ]]; then
           ac_gdz_glut_incdir_e5='"'`cygpath -w $ac_gdz_glut_dir/include`'"'
           ac_gdz_glut_libdir_e5='"'`cygpath -w $ac_gdz_glut_dir/lib`'"'
           ac_gdz_glut_lib_e5='glut32.lib'
        else
           ac_gdz_glut_incdir_e5=$ac_gdz_glut_dir/include
           ac_gdz_glut_libdir_e5=$ac_gdz_glut_dir/lib
           ac_gdz_glut_lib_e5='-lglut'
        fi
    fi

    ac_gdz_common_glut_in_e5=$ac_gdz_commonconf_dir/commonGLUT.in
    ac_gdz_common_glut_e5=$ac_gdz_commonpackage_dir/commonGLUT.mk

    AC_SUBST(ac_gdz_glut_incdir_e5)
    AC_SUBST(ac_gdz_glut_libdir_e5)
    AC_SUBST(ac_gdz_glut_lib_e5)
   
    touch confdefs.h

    AC_OUTPUT($ac_gdz_common_glut_e5:$ac_gdz_common_glut_in_e5)
])


AC_DEFUN(AC_GDZ_WRITE_COMMON_QT,
[
dnl e5

    changequote(<<, >>)dnl

    ac_gdz_qt_lib_e6=
    ac_gdz_qt_incdir_e6=
    ac_gdz_qt_libdir_e6=
    ac_gdz_qt_moc_e6=

    if [[ -n "$ac_gdz_qt_dir" ]]; then
        if [[ $build_os = cygwin ]]; then
           ac_gdz_qt_incdir_e6='"'`cygpath -w $ac_gdz_qt_dir/include`'"'
           ac_gdz_qt_libdir_e6='"'`cygpath -w $ac_gdz_qt_dir/lib`'"'
           ac_gdz_qt_moc_e6=$ac_gdz_qt_dir/bin/moc
           ac_gdz_qt_lib_e6=`cd $ac_gdz_qt_dir/lib; ls qt[0-9]*.lib`
            
        else
           ac_gdz_qt_incdir_e6=$ac_gdz_qt_dir/include
           ac_gdz_qt_libdir_e6=$ac_gdz_qt_dir/lib
           ac_gdz_qt_moc_e6=$ac_gdz_qt_dir/bin/moc
           ac_gdz_qt_lib_e6='-lqt'
        fi
    fi

    changequote([, ])dnl

    ac_gdz_common_qt_in_e6=$ac_gdz_commonconf_dir/commonQT.in
    ac_gdz_common_qt_e6=$ac_gdz_commonpackage_dir/commonQT.mk

    AC_SUBST(ac_gdz_qt_incdir_e6)
    AC_SUBST(ac_gdz_qt_libdir_e6)
    AC_SUBST(ac_gdz_qt_lib_e6)
    AC_SUBST(ac_gdz_qt_moc_e6)
   
    touch confdefs.h

    AC_OUTPUT($ac_gdz_common_qt_e6:$ac_gdz_common_qt_in_e6)
])



AC_DEFUN(AC_GDZ_WRITE_SYSTEM_COMMON,
[
dnl e7

    ac_gdz_common_sys_mk_os_base_e7=$build_os
    ac_gdz_common_sys_mk_build_env_e7=$build

    ac_gdz_common_sys_mk_in_e7=$ac_gdz_commonconf_dir/commonSys.mk.in
    ac_gdz_common_sys_mk_e7=$ac_gdz_common_dir/common.mk

    AC_SUBST(ac_gdz_common_sys_mk_os_base_e7)
    AC_SUBST(ac_gdz_common_sys_mk_build_env_e7)

    touch confdefs.h

    AC_OUTPUT($ac_gdz_common_sys_mk_e7:$ac_gdz_common_sys_mk_in_e7)
])

AC_DEFUN(AC_GDZ_WRITE_COMMON_GL,
[
dnl e8

    ac_gdz_common_gl_in_e4=$ac_gdz_commonconf_dir/commonGL.in
    ac_gdz_common_gl_e4=$ac_gdz_commonpackage_dir/commonGL.mk

    touch confdefs.h

    AC_OUTPUT($ac_gdz_common_gl_e4:$ac_gdz_common_gl_in_e4)
])

AC_DEFUN(AC_GDZ_WRITE_COMMON_TIF,
[
dnl e9

    ac_gdz_tif_lib_e9=
    ac_gdz_tif_incdir_e9=
    ac_gdz_tif_libdir_e9=

    if [[ "$with_tif" = yes ]]; then
        if [[ $build_os = cygwin ]]; then
           ac_gdz_tif_lib_e9='tif32.lib'
        else
           ac_gdz_tif_lib_e9='-ltiff'
        fi
    elif [[ -n "$ac_gdz_tif_dir" ]]; then
        if [[ $build_os = cygwin ]]; then
           ac_gdz_tif_incdir_e9='"'`cygpath -w $ac_gdz_tif_dir/include`'"'
           ac_gdz_tif_libdir_e9='"'`cygpath -w $ac_gdz_tif_dir/lib`'"'
           ac_gdz_tif_lib_e9='tif32.lib'
        else
           ac_gdz_tif_incdir_e9=$ac_gdz_tif_dir/include
           ac_gdz_tif_libdir_e9=$ac_gdz_tif_dir/lib
           ac_gdz_tif_lib_e9='-ltiff'
        fi
    fi

    ac_gdz_common_tif_in_e9=$ac_gdz_commonconf_dir/commonTIF.in
    ac_gdz_common_tif_e9=$ac_gdz_commonpackage_dir/commonTIF.mk

    AC_SUBST(ac_gdz_tif_incdir_e9)
    AC_SUBST(ac_gdz_tif_libdir_e9)
    AC_SUBST(ac_gdz_tif_lib_e9)
   
    touch confdefs.h

    AC_OUTPUT($ac_gdz_common_tif_e9:$ac_gdz_common_tif_in_e9)
])

AC_DEFUN(AC_GDZ_WRITE_COMMON_JPG,
[
dnl e10

    ac_gdz_jpg_lib_e10=
    ac_gdz_jpg_incdir_e10=
    ac_gdz_jpg_libdir_e10=

    if [[ "$with_jpg" = yes ]]; then
        if [[ $build_os = cygwin ]]; then
           ac_gdz_jpg_lib_e10='jpg32.lib'
        else
           ac_gdz_jpg_lib_e10='-ljpeg'
        fi
    elif [[ -n "$ac_gdz_jpg_dir" ]]; then
        if [[ $build_os = cygwin ]]; then
           ac_gdz_jpg_incdir_e10='"'`cygpath -w $ac_gdz_jpg_dir/include`'"'
           ac_gdz_jpg_libdir_e10='"'`cygpath -w $ac_gdz_jpg_dir/lib`'"'
           ac_gdz_jpg_lib_e10='jpg32.lib'
        else
           ac_gdz_jpg_incdir_e10=$ac_gdz_jpg_dir/include
           ac_gdz_jpg_libdir_e10=$ac_gdz_jpg_dir/lib
           ac_gdz_jpg_lib_e10='-ljpeg'
        fi
    fi

    ac_gdz_common_jpg_in_e10=$ac_gdz_commonconf_dir/commonJPG.in
    ac_gdz_common_jpg_e10=$ac_gdz_commonpackage_dir/commonJPG.mk

    AC_SUBST(ac_gdz_jpg_incdir_e10)
    AC_SUBST(ac_gdz_jpg_libdir_e10)
    AC_SUBST(ac_gdz_jpg_lib_e10)
   
    touch confdefs.h

    AC_OUTPUT($ac_gdz_common_jpg_e10:$ac_gdz_common_jpg_in_e10)
])

AC_DEFUN(AC_GDZ_WRITE_COMMON_PNG,
[
dnl e11

    ac_gdz_png_lib_e11=
    ac_gdz_png_incdir_e11=
    ac_gdz_png_libdir_e11=

    if [[ "$with_png" = yes ]]; then
        if [[ $build_os = cygwin ]]; then
           ac_gdz_png_lib_e11='png32.lib'
        else
           ac_gdz_png_lib_e11='-lpng -lz'
        fi
    elif [[ -n "$ac_gdz_png_dir" ]]; then
        if [[ $build_os = cygwin ]]; then
           ac_gdz_png_incdir_e11='"'`cygpath -w $ac_gdz_png_dir/include`'"'
           ac_gdz_png_libdir_e11='"'`cygpath -w $ac_gdz_png_dir/lib`'"'
           ac_gdz_png_lib_e11='png32.lib'
        else
           ac_gdz_png_incdir_e11=$ac_gdz_png_dir/include
           ac_gdz_png_libdir_e11=$ac_gdz_png_dir/lib
           ac_gdz_png_lib_e11='-lpng'
        fi
    fi

    ac_gdz_common_png_in_e11=$ac_gdz_commonconf_dir/commonPNG.in
    ac_gdz_common_png_e11=$ac_gdz_commonpackage_dir/commonPNG.mk

    AC_SUBST(ac_gdz_png_incdir_e11)
    AC_SUBST(ac_gdz_png_libdir_e11)
    AC_SUBST(ac_gdz_png_lib_e11)
   
    touch confdefs.h

    AC_OUTPUT($ac_gdz_common_png_e11:$ac_gdz_common_png_in_e11)
])

AC_DEFUN(AC_GDZ_WRITE_COMMON_MNG,
[
dnl e12

    ac_gdz_mng_lib_e12=
    ac_gdz_mng_incdir_e12=
    ac_gdz_mng_libdir_e12=

    if [[ "$with_mng" = yes ]]; then
        if [[ $build_os = cygwin ]]; then
           ac_gdz_mng_lib_e12='mng32.lib'
        else
           ac_gdz_mng_lib_e12='-lmng'
        fi
    elif [[ -n "$ac_gdz_mng_dir" ]]; then
        if [[ $build_os = cygwin ]]; then
           ac_gdz_mng_incdir_e12='"'`cygpath -w $ac_gdz_mng_dir/include`'"'
           ac_gdz_mng_libdir_e12='"'`cygpath -w $ac_gdz_mng_dir/lib`'"'
           ac_gdz_mng_lib_e12='mng32.lib'
        else
           ac_gdz_mng_incdir_e12=$ac_gdz_mng_dir/include
           ac_gdz_mng_libdir_e12=$ac_gdz_mng_dir/lib
           ac_gdz_mng_lib_e12='-lmng'
        fi
    fi

    ac_gdz_common_mng_in_e12=$ac_gdz_commonconf_dir/commonMNG.in
    ac_gdz_common_mng_e12=$ac_gdz_commonpackage_dir/commonMNG.mk

    AC_SUBST(ac_gdz_mng_incdir_e12)
    AC_SUBST(ac_gdz_mng_libdir_e12)
    AC_SUBST(ac_gdz_mng_lib_e12)
   
    touch confdefs.h

    AC_OUTPUT($ac_gdz_common_mng_e12:$ac_gdz_common_mng_in_e12)
])

AC_DEFUN(AC_GDZ_WRITE_COMMON_GIF,
[
dnl e13

    ac_gdz_gif_lib_e13=
    ac_gdz_gif_incdir_e13=
    ac_gdz_gif_libdir_e13=

    if [[ "$with_gif" = yes ]]; then
        if [[ $build_os = cygwin ]]; then
           ac_gdz_gif_lib_e13=
        else
           ac_gdz_gif_lib_e13=
        fi
    elif [[ -n "$ac_gdz_gif_dir" ]]; then
        if [[ $build_os = cygwin ]]; then
           ac_gdz_gif_incdir_e13=
           ac_gdz_gif_libdir_e13=
           ac_gdz_gif_lib_e13=
        else
           ac_gdz_gif_incdir_e13=
           ac_gdz_gif_libdir_e13=
           ac_gdz_gif_lib_e13=
        fi
    fi

    ac_gdz_common_gif_in_e13=$ac_gdz_commonconf_dir/commonGIF.in
    ac_gdz_common_gif_e13=$ac_gdz_commonpackage_dir/commonGIF.mk

    AC_SUBST(ac_gdz_gif_incdir_e13)
    AC_SUBST(ac_gdz_gif_libdir_e13)
    AC_SUBST(ac_gdz_gif_lib_e13)
   
    touch confdefs.h

    AC_OUTPUT($ac_gdz_common_gif_e13:$ac_gdz_common_gif_in_e13)
])


AC_DEFUN(AC_GDZ_WRITE_COMMON_MYRINET,
[
dnl e14

    ac_gdz_myrinet_lib_e14=
    ac_gdz_myrinet_incdir_e14=
    ac_gdz_myrinet_libdir_e14=

    if [[ "$with_myrinet" = yes ]]; then
        if [[ $build_os = cygwin ]]; then
           ac_gdz_myrinet_lib_e14='gm32.lib'
        else
           ac_gdz_myrinet_lib_e14='-lgm'
        fi
    elif [[ -n "$ac_gdz_myrinet_dir" ]]; then
        if [[ $build_os = cygwin ]]; then
           ac_gdz_myrinet_incdir_e14='"'`cygpath -w $ac_gdz_myrinet_dir/include`'"'
           ac_gdz_myrinet_libdir_e14='"'`cygpath -w $ac_gdz_myrinet_dir/lib`'"'
           ac_gdz_myrinet_lib_e14='gm32.lib'
        else
           ac_gdz_myrinet_incdir_e14=$ac_gdz_myrinet_dir/include
           ac_gdz_myrinet_libdir_e14=$ac_gdz_myrinet_dir/lib
           ac_gdz_myrinet_lib_e14='-lgm'
        fi
    fi

    ac_gdz_common_myrinet_in_e14=$ac_gdz_commonconf_dir/commonMYRINET.in
    ac_gdz_common_myrinet_e14=$ac_gdz_commonpackage_dir/commonMYRINET.mk

    AC_SUBST(ac_gdz_myrinet_incdir_e14)
    AC_SUBST(ac_gdz_myrinet_libdir_e14)
    AC_SUBST(ac_gdz_myrinet_lib_e14)
   
    touch confdefs.h

    AC_OUTPUT($ac_gdz_common_myrinet_e14:$ac_gdz_common_myrinet_in_e14)
])
