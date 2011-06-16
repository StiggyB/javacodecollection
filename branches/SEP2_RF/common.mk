# This is an automatically generated record.
# The area between QNX Internal Start and QNX Internal End is controlled by
# the QNX IDE properties.

ifndef QCONFIG
QCONFIG=qconfig.mk
endif
include $(QCONFIG)

#===== USEFILE - the file containing the usage message for the application. 
USEFILE=

# Next lines are for C++ projects only

EXTRA_SUFFIXES+=cxx cpp

#===== LDFLAGS - add the flags to the linker command line.
LDFLAGS+=-lang-c++

VFLAG_g=-gstabs+

#===== EXTRA_SRCVPATH - a space-separated list of directories to search for source files.
EXTRA_SRCVPATH+=$(PROJECT_ROOT)/Controller  \
	$(PROJECT_ROOT)/HAL $(PROJECT_ROOT)/Lampen  \
	$(PROJECT_ROOT)/Thread $(PROJECT_ROOT)/Tests  \
	$(PROJECT_ROOT)/Serial $(PROJECT_ROOT)/FSM  \
	$(PROJECT_ROOT)/Timer $(PROJECT_ROOT)/Functor

#===== LIBS - a space-separated list of library items to be included in the link.
LIBS+=phrender ph cpt_terminal

include $(MKFILES_ROOT)/qmacros.mk

#===== EXTRA_OBJS - object files and libraries contributed additionaly on link/archive step
EXTRA_OBJS+=C:/QNX650/target/qnx6/x86/lib/libioaccess.a  \
	C:/QNX650/target/qnx6/x86/lib/libioaccess_g.a  \
	C:/QNX650/target/qnx6/x86/lib/libcpt_terminal.a

ifndef QNX_INTERNAL
QNX_INTERNAL=$(PROJECT_ROOT)/.qnx_internal.mk
endif
include $(QNX_INTERNAL)

include $(MKFILES_ROOT)/qtargets.mk

OPTIMIZE_TYPE_g=none
OPTIMIZE_TYPE=$(OPTIMIZE_TYPE_$(filter g, $(VARIANTS)))

