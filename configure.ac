AC_PREREQ([2.69])
define(_CLIENT_VERSION_MAJOR, 23)
define(_CLIENT_VERSION_MINOR, 2)
define(_CLIENT_VERSION_BUILD, 0)
define(_CLIENT_VERSION_RC, 0)
define(_CLIENT_VERSION_IS_RELEASE, true)
define(_COPYRIGHT_YEAR, 2023)
define(_COPYRIGHT_HOLDERS,[The %s developers])
define(_COPYRIGHT_HOLDERS_SUBSTITUTION,[[Paperclips Core]])
AC_INIT([Paperclips Core],m4_join([.], _CLIENT_VERSION_MAJOR, _CLIENT_VERSION_MINOR, _CLIENT_VERSION_BUILD)m4_if(_CLIENT_VERSION_RC, [0], [], [rc]_CLIENT_VERSION_RC),[https://github.com/paperclips-project/paperclips-core/issues],[paperclips],[https://paperclips.org/])
AC_CONFIG_SRCDIR([src/validation.cpp])
AC_CONFIG_HEADERS([src/config/bitcoin-config.h])
AC_CONFIG_AUX_DIR([build-aux])
AC_CONFIG_MACRO_DIR([build-aux/m4])

m4_ifndef([PKG_PROG_PKG_CONFIG], [m4_fatal([PKG_PROG_PKG_CONFIG macro not found. Please install pkg-config and re-run autogen.sh])])
PKG_PROG_PKG_CONFIG
if test "$PKG_CONFIG" = ""; then
  AC_MSG_ERROR([pkg-config not found])
fi

BITCOIN_DAEMON_NAME=paperclipsd
BITCOIN_GUI_NAME=paperclips-qt
BITCOIN_CLI_NAME=paperclips-cli
BITCOIN_TX_NAME=paperclips-tx
BITCOIN_UTIL_NAME=paperclips-util
BITCOIN_WALLET_TOOL_NAME=paperclips-wallet
dnl Multi Process
BITCOIN_MP_NODE_NAME=paperclips-node
BITCOIN_MP_GUI_NAME=paperclips-gui

dnl Unless the user specified ARFLAGS, force it to be cr
AC_SUBST(ARFLAGS)

AC_CANONICAL_HOST

AM_INIT_AUTOMAKE([no-define subdir-objects foreign])

AC_PROG_CXX
AC_PROG_CC
AC_PROG_MAKE_SET

LT_INIT([pic-only])

AC_OUTPUT([
  Makefile
])
