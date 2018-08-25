target = m_who
source = m_who.c

m_cp : $(source) build
	gcc -g -o $(target) $(source);
	mv *.dSYM build;
	mv $(target) build;
build :
	mkdir build;
.PHONY : clean
clean :
	rm -r build 

