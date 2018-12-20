# r-Score #

## EVEN platform framework testing algorithm sample application ##

This sample developed for testing influence of original algorithm to rating value of main parameters included to him.

### Prepare for building ###

### What is this repository for? ###

 * Quick summary
 * Version 
 1.0 
 * [Learn Markdown](https://bitbucket.org/tutorials/markdowndemo)

### How do I get set up? ###

* Summary of set up

 1.Install on Orange Pi PC lubuntu OS - * [hear](http://www.instructables.com/id/Install-LUBUNTU-OS-on-Orange-Pi-Zero-Orange-Pi/);
 
 2.Install webiopi - * [Orange Pi forum](http://www.orangepi.org/orangepibbsen/forum.php?mod=viewthread&tid=1601);
 
 3.Install OpenOCD - JTAG over Orange PI PC - * [manual](https://github.com/synthetos/PiOCD/wiki/Using-a-Raspberry-Pi-as-a-JTAG-Dongle);
 
 4.Install WebSDR - * [the good practic of](http://sq7mru.blogspot.ru/);
 
 For revision and update need install Quartus Prime (as minimalis) or will need translate verilog's to Altium Designer 17.1 workspace;
 For ExtIO need VC2008..2011 - for MS(Win) version, for other all OS's - need Qt more than 5.0 verson, look up it's qt.org.

## EVEN Network Platform Simulation Application 

This application developed for research some main processes peer-2-peer network, contains realistic nodes proceedes imitation application.
It models included:
* distributed network topology and its functionally imitation with realistic constrains;
* node transactions job with hash operations imitation with block-chain components model;
* any algorithm fabric and network processes imitation with it;

## License

See [LICENSE](LICENSE).

## Installing even-boffin from a package

Packages are available for

* Ubuntu 18.04 x64 LTS Linux: [even-boffin-ubuntu](https://evenfound.org/packages/event-network-ubuntu/)
* Windows 10 MSYS2 (mingw64): [even-boffin-windows](https://evenfound.org/packages/event-network-windows/)

Packaging for your favorite distribution would be a welcome contribution!

## Compiling the even-boffin from source

### On Linux:

(Tested on Ubuntu 18.04 x64)

1. Install EVEN Platform dependencies

  - For Debian distributions (Ubuntu)

	`sudo apt install build-essential cmake libboost-all-dev miniupnpc libunbound-dev graphviz doxygen libunwind8-dev pkg-config libssl-dev libzmq3-dev libsodium-dev libhidapi-dev`

2. Install Qt:

  *Note*: Qt 5.7 is the minimum version required to build. This makes **some** distributions (mostly based on debian, like Ubuntu 16.x or Linux Mint 18.x) obsolete. You can still build the GUI if you install an [official Qt release](https://wiki.qt.io/Install_Qt_5_on_Ubuntu), but this is not officially supported.

  - For Ubuntu 17.10+

    `sudo apt install qtbase5-dev qt5-default qtdeclarative5-dev qml-module-qtquick-controls qml-module-qtquick-controls2 qml-module-qtquick-dialogs qml-module-qtquick-xmllistmodel qml-module-qt-labs-settings qml-module-qt-labs-folderlistmodel qttools5-dev-tools qml-module-qtquick-templates2`

3. Clone repository

    `git clone https://github.com/evenfound/even-network.git`

4. Build

    ```
    cd even-network/even-boffin
    mkdir build
    cd build
    cmake ..
    cd -
    ```

The executable can be found in the ./bin folder.

### On Windows:

The even-boffin on Windows is 64 bits only; 32-bit Windows builds are not officially supported anymore.

1. Install [MSYS2](https://www.msys2.org/), follow the instructions on that page on how to update system and packages to the latest versions

2. Open an 64-bit MSYS2 shell: Use the *MSYS2 MinGW 64-bit* shortcut, or use the `msys2_shell.cmd` batch file with a `-mingw64` parameter

3. Install MSYS2 packages for EVEN Platform dependencies; the needed 64-bit packages have `x86_64` in their names

    ```
    pacman -S mingw-w64-x86_64-toolchain make mingw-w64-x86_64-cmake mingw-w64-x86_64-boost mingw-w64-x86_64-openssl mingw-w64-x86_64-zeromq mingw-w64-x86_64-libsodium mingw-w64-x86_64-hidapi
    ```

    You find more details about those dependencies in the [EVEN Platform documentation](https://github.com/evenfound/even-network/doc). Note that that there is no more need to compile Boost from source; like everything else, you can install it now with a MSYS2 package.

4. Install Qt5

    ```
    pacman -S mingw-w64-x86_64-qt5
    ```

    There is no more need to download some special installer from the Qt website, the standard MSYS2 package for Qt will do in almost all circumstances.

5. Install git

    ```
    pacman -S git
    ```

6. Clone repository

    ```
    git clone https://github.com/evenfound/even-network.git
    ```

7. Build

    ```
    cd even-network/even-boffin
    mkdir build
    cd build
    cmake -G "MSYS Makefiles" ..
    cd -
    ```

The executable can be found in the `./bin` directory.