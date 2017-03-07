all:main.cpp bmp.h bmp.cpp color.h color.cpp Vector2.h Vector2.cpp
	g++ -o Raster.exe -lpsapi -lgcc -lstdc++ main.cpp bmp.h bmp.cpp color.h color.cpp Vector2.h Vector2.cpp 2> error.txt
	Raster.exe
	
clean:
	del *.obj *.exe