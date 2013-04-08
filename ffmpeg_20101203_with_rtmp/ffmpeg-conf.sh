SDL_CFLAGS=/mingw/include 
SDL_LIBS=/mingw/lib 
./configure --extra-cflags="-fno-common -mms-bitfields -DWIN32" --enable-memalign-hack --enable-shared --disable-static --enable-w32threads