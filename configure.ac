AC_INIT([cairo-xemmai], [200911])
AM_INIT_AUTOMAKE([foreign nostdinc dist-bzip2 no-dist-gzip])
AC_CONFIG_SRCDIR([cairo/xemmai/cairo.cc])

PKG_CHECK_MODULES([CAIRO], [cairo >= 1.8])

if test "${CXXFLAGS+set}" != set; then
	CXXFLAGS=
fi
AC_PROG_CXX
AM_PROG_LIBTOOL
AM_DISABLE_STATIC

AC_C_INLINE
AC_TYPE_PID_T
AC_TYPE_SIZE_T

AC_ARG_WITH(
	[xemmai],
	AS_HELP_STRING([--with-xemmai], [specify xemmai executable [[default=xemmai]]]),
	[xemmai_executable=${withval}],
	[xemmai_executable=xemmai]
)
AC_SUBST(XEMMAI_MODULE_PATH)
XEMMAI_MODULE_PATH=`${xemmai_executable} --default-module-path`
AC_ARG_ENABLE(
	[debug],
	AS_HELP_STRING([--enable-debug], [turn on debugging]),
	[case "${enableval}" in
	  yes) debug=true ;;
	  no) debug=false ;;
	  *) AC_MSG_ERROR([bad value ${enableval} for --enable-debug]) ;;
	 esac],
	[debug=false]
)
AM_CONDITIONAL([DEBUG], [test x$debug = xtrue])
AC_ARG_ENABLE(
	[profile],
	AS_HELP_STRING([--enable-profile], [turn on profiling]),
	[case "${enableval}" in
	  yes) profile=true ;;
	  no) profile=false ;;
	  *) AC_MSG_ERROR([bad value ${enableval} for --enable-profile]) ;;
	 esac],
	[profile=false]
)
AM_CONDITIONAL([PROFILE], [test x$profile = xtrue])

AC_CONFIG_HEADERS([cairo/xemmai/configure.h])
AC_CONFIG_FILES([
	Makefile
	cairo/xemmai/Makefile
])
AC_OUTPUT
