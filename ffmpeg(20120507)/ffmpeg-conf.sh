SDL_CFLAGS=/mingw/include 
SDL_LIBS=/mingw/lib 
#./configure --extra-cflags=-fno-common --extra-cflags=-DWIN32 --enable-memalign-hack --enable-shared --disable-static --enable-w32threads --enable-yasm --disable-ssse3 --disable-sse --enable-protocols --disable-encoders --disable-decoders --disable-muxers --disable-demuxers --enable-demuxer=flv --enable-decoder=mp3 --enable-decoder=aac --enable-decoder=h264 --enable-muxer=mp4
./configure --extra-cflags=-fno-common --extra-cflags=-DWIN32 --enable-memalign-hack --enable-shared --disable-static --enable-w32threads --enable-yasm --disable-ssse3 --disable-sse --enable-protocols --disable-encoders --enable-decoders --disable-muxers --enable-demuxers --enable-muxer=mp4 --enable-muxer=flv --enable-encoder=aac --disable-devices --disable-avfilter --disable-filters --enable-network --disable-bsfs --enable-asm --extra-libs="-lgcc" --disable-stripping  --disable-postproc --disable-avdevice --disable-decoder=mp1float --disable-decoder=mp2float --disable-decoder=mp3float --disable-decoder=mp3adufloat --disable-decoder=mp3on4float