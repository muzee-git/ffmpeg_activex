SDL_CFLAGS=/mingw/include 
SDL_LIBS=/mingw/lib 
./configure --extra-cflags=-fno-common --extra-cflags=-DWIN32 --enable-memalign-hack --enable-shared --disable-static --enable-w32threads --enable-yasm --disable-ssse3 --disable-sse --disable-mmx2 --disable-mmx --enable-protocols --enable-demuxer=asf