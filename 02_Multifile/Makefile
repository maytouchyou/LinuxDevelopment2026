GENERATES = $(progs) README liboutput_static.a liboutput.so $(txt)
TRASH = *.o o.*
CFLAGS = -fPIC
args = 0 1 3
progs = prog prog-a prog-so
txt = $(foreach p,$(progs),$(foreach a,$(args),$(p).$(a)))
cmptxt = $(addsuffix .cmp,$(txt))

suf = $(suffix $(basename $(1)))
base = $(basename $(basename $(1)))

argnum = $(subst .,,$(suffix $(1)))
#base = $(basename $(1))

#suf = $(suffix $(basename $1))
#base = $(subst $(suffix $(basename $1)),,$(basename $1))

all:    README $(progs) test

test:	$(txt) $(cmptxt)

$(txt):	$(progs)
	LD_LIBRARY_PATH=. ./$(basename $@) `seq -s' ' $(call argnum,$@)` 2> $@

$(cmptxt):	$(txt) 
	-cmp $(addsuffix $(call suf,$@), $(filter-out $(call base,$@),$(progs)))


prog:   const.o fun.o prog.o

prog-a:	prog.o liboutput_static.a
	cc -L. prog.o -loutput_static -o $@

prog-so:	prog.o liboutput.so
	cc -L. prog.o -loutput -o $@

README: prog
	./$< 2> $@

fun.o:	outlib.h

liboutput_static.a:	const.o fun.o
	ar -rcs $@ $^

liboutput.so:	const.o fun.o
	cc -shared $^ -o $@

clean:
	rm -rf $(GENERATES) $(TRASH)

distclean:      clean
	rm -rf $(GENERATES)
