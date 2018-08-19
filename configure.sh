# This file fetches required libraries for Varuna to run
# These include:
#    SDL2
#    SDL_image
#    SDL_ttf

mkdir -p varuna_downloads
cd varuna_downloads

# SDL2
echo "Downloading SDL2..."
wget https://www.libsdl.org/release/SDL2-2.0.8.tar.gz

echo "Extracting SDL2..."
tar -xzf SDL2-2.0.8.tar.gz

echo "Installing SDL2..."
cd SDL2-2.0.8 && ./configure --prefix=/usr && make && sudo make install

# SDL_image
echo "Downloading SDL_image..."
wget https://www.libsdl.org/projects/SDL_image/release/SDL2_image-2.0.3.tar.gz

echo "Extracting SDL_image..."
tar -xzf SDL2_image-2.0.3.tar.gz

echo "Installing SDL_image..."
cd SDL2_image-2.0.3 && ./configure --prefix=/usr && make && sudo make install

# SDL_ttf
echo "Downloading SDL_ttf..."
wget https://www.libsdl.org/projects/SDL_ttf/release/SDL2_ttf-2.0.14.tar.gz

echo "Extracting SDL_ttf..."
tar -xzf SDL2_ttf-2.0.14.tar.gz

echo "Installing SDL_ttf..."
cd SDL2_ttf-2.0.14 && ./configure --prefix=/usr && make && sudo make install

cd ..
rm -r varuna_downloads
