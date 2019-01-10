# EVEN Platform Framework
Copyright (c) 2018, The EVEN Found Project

## Development resources

- Web: [evenfound.org](https://evenfound.org)
- Mail: [dev@evenfound.org](mailto:dev@evenfound.org)
- Github: [https://github.com/evenfound/even-network](https://github.com/evenfound/even-network)
- IRC: [#evenfound-dev on Freenode](irc://chat.freenode.net/#evenfound-dev)
- Translation platform (Pootle): [translate.evenfound.org](https://translate.evenfound.org)

## Introduction

EVEN Network — is an open cross-chain platform with EVEN cryptocurrency that allows users to interact with more than one blockchain at a time.

**Cross-chain:** Transactions involving more than one blockchain through a single entry point.

**Reliability:** A high degree of protection for digital assets due to unique cryptographic solutions.

**Control:** Private keys are always under the control of a user.

**Scalability:** The network will continue to run quickly even as the number of participants grows, and external services can be integrated into it using the open API.

## About this project

This is the core EVEN Network Platform API all base interfaces, simulation applications and prerequisites including. It is open source and completely free to use without restrictions, except for those specified in the license agreement below. There are no restrictions on anyone creating an alternative implementation of EVEN Platform that uses the protocol and network in a compatible manner.

As with many development projects, the repository on Github is considered to be the "staging" area for the latest changes. Before changes are merged into that branch on the main repository, they are tested by individual developers in their own branches, submitted as a pull request, and then subsequently tested by contributors who focus on testing and code reviews. That having been said, the repository should be carefully considered before using it in a production environment, unless there is a patch in the repository for a particular show-stopping issue you are experiencing. It is generally a better idea to use a tagged release for stability.

## License

See [LICENSE](LICENSE).

## Installing the EVEN Platform API from a package

Packages are available for

* Ubuntu 18.04 x64 LTS Linux: [even-network-ubuntu](https://evenfound.org/packages/event-network-ubuntu/)
* Windows 10 MSYS2 (mingw64): [even-network-windows](https://evenfound.org/packages/event-network-windows/)

Packaging for your favorite distribution would be a welcome contribution!

## Compiling the EVEN Platform Application from source

### On Linux:

(Tested on Ubuntu 18.04 x64)

1. Install EVEN Platform dependencies

  - For Debian distributions (Ubuntu)

    `sudo apt install build-essential cmake libboost-all-dev miniupnpc libunbound-dev graphviz doxygen libunwind8-dev pkg-config libssl-dev libzmq3-dev libsodium-dev libhidapi-dev`

2. Install Qt:

  *Note*: Qt 5.10 is the minimum version required to build. This makes **some** distributions (mostly based on debian, like Ubuntu 16.x or Linux Mint 18.x) obsolete. You can still build the GUI if you install an [official Qt release](https://wiki.qt.io/Install_Qt_5_on_Ubuntu), but this is not officially supported.

  - For Ubuntu 17.10+

    `sudo apt install qtbase5-dev qtbase5-private-dev qt5-default qtdeclarative5-dev qml-module-qtquick-controls qml-module-qtquick-controls2 qml-module-qtquick-dialogs qml-module-qtquick-xmllistmodel qml-module-qt-labs-settings qml-module-qt-labs-folderlistmodel qttools5-dev-tools libqt5websockets5-dev qml-module-qtquick-templates2`

3. Clone repository and submodules to root of home directory

    ```
    git clone https://github.com/evenfound/even-network.git
    git submodule init
    git submodule update
    ```

4. Install cmake

    `sudo apt-get install cmake`

5. Build

    ```
    cd even-network
    QT_SELECT=5 ./build.ubuntu.sh
    ```

The executable can be found in the ./bin folder.

### On Windows:

The EVEN Platform on Windows is 64 bits only; 32-bit Windows builds are not officially supported anymore.

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

6. Clone repository and submodules to root of home directory

    ```
    git clone https://github.com/evenfound/even-network.git
    git submodule init
    git submodule update

    ```

7. Build

    ```
    cd even-network
    ./build.msys2.sh
    ```

The executable can be found in the `./bin` directory.
