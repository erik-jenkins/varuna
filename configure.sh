# This file fetches required libraries for Varuna to run
# These include:
#    SDL2
#    SDL_image
#    SDL_ttf

# SDL2
wget https://www.libsdl.org/release/SDL2-2.0.8.tar.gz
tar -xzf SDL2-2.0.8.tar.gz
pushd SDL2-2.0.8 && ./configure --prefix=/usr && make && sudo make install && popd

# SDL_image
wget https://www.libsdl.org/projects/SDL_image/release/SDL2_image-2.0.3.tar.gz
tar -xzf SDL2_image-2.0.3.tar.gz
pushd SDL2_image-2.0.3 && ./configure --prefix=/usr && make && sudo make install && popd

# SDL_ttf
wget https://www.libsdl.org/projects/SDL_ttf/release/SDL2_ttf-2.0.14.tar.gz
tar -xzf SDL2_ttf-2.0.14.tar.gz
pushd SDL2_ttf-2.0.14 && ./configure --prefix=/usr && make && sudo make install && popd
