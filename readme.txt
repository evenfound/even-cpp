Install prerequisites, build tool and build project(s), sketchily:

1. Install Qt last version (project was developed with 5.11 ver.);
2. Install git;
3. Clone repository to choosen directpry (git clone);
4. Launch terminal (bash console from git distributeve installed - under windows) and enter to clones directory and make 'git submodule init' and 'git submodule update';
5. After that make copy patch.diff from project root directory to prerequisites/QtWebApp and make 'git apply patch.diff' in the terminal (git bash console);
6. Install last version of python;
7. Install cmake (under windows x64 get the distro from https://github.com/Kitware/CMake/releases/download/v3.13.1/cmake-3.13.1-win64-x64.msi link )

