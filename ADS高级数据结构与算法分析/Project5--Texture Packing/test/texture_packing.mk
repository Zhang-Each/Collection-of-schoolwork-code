objects = texture_packing_for_test.o
CPP = g++
CPPFLAGS = -std=c++11

texture_packing : $(objects)
	$(CPP) $(CPPFLAGS) $(objects) -o texture_packing

#清除.o文件
.PHONY : clean
clean :
	-rm $(objects)

