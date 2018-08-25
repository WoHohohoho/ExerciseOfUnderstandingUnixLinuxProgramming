target = m_ls 
source = m_ls.c

m_cp : $(source) build
	gcc -g -o $(target) $(source);
	mv *.dSYM build;
	mv $(target) build;
build :
	mkdir build;
.PHONY : clean
clean :
	rm -r build 

