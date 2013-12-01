#######################################
# The list of executables we are building seperated by spaces
# the 'bin_' indicates that these build products will be installed
# in the $(bindir) directory. For example /usr/bin
#bin_PROGRAMS=filterlib_test

# Because a.out is only a sample program we don't want it to be installed.
# The 'noinst_' prefix indicates that the following targets are not to be
# installed.
noinst_PROGRAMS=filterlib_test

#######################################
# Build information for each executable. The variable name is derived
# by use the name of the executable with each non alpha-numeric character is
# replaced by '_'. So a.out becomes a_out and the appropriate suffex added.
# '_SOURCES' for example.

# Sources for the a.out 
filterlib_test_SOURCES= filterlib_test.c

# Linker options for a.out
filterlib_test_LDFLAGS = $(top_srcdir)/libFilter/libFilter.la

# Compiler options for a.out
filterlib_test_CPPFLAGS = -I$(top_srcdir)/include
