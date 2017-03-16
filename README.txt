build:
	$ mkdir build && cd build
	$ cmake ..
	$ make
	
if you SDL2 path is not standard, add the following flags to cmake 
	( cmake -Dflag=/path-to .. ):
	SDL2_INCLUDE_DIR=/path-to/include
	SDL2_LIBRARY=/path-to/lib
	SDL2MAIN_LIBRARY=/path-to/lib