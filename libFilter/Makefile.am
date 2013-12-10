#######################################
# The list of libraries we are building seperated by spaces.
# The 'lib_' indicates that these build products will be installed
# in the $(libdir) directory. For example /usr/lib
lib_LTLIBRARIES = libFilterIIR.la

#######################################
# Build information for each library

# Sources for libFilterIIR
libFilterIIR_la_SOURCES = libFilterIIR.c libFilterFIR.c

# Linker options libTestProgram
libFilterIIR_la_LDFLAGS = 

# Compiler options. Here we are adding the include directory
# to be searched for headers included in the source code.
libFilterIIR_la_CPPFLAGS = -I$(top_srcdir)/include

