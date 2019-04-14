mkdir build
cd build
cmake -GNinja -DJP2KFLAG=OFF -Dpybindings=OFF -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=$PREFIX ../isis
ninja install
