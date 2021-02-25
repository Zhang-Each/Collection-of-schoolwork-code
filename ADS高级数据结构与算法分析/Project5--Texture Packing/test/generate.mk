objects = test_generator.o
CPP = g++
CPPFLAGS = -std=c++11

generator : $(objects)
	$(CPP) $(CPPFLAGS) $(objects) -o generator

#清除.o文件
.PHONY : clean
clean :
	-rm $(objects)

