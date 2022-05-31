# AutoInstall

## Description
AutoInstall is a program under the GPL 3.0 license for quick installation of programs from repositories of systems based on Arch Linux, Debian and the like. Very convenient when reinstalling the system.

## Build and install automatically

Open a terminal and enter the following commands:

`su root`

`chmod +x install.sh`

`./install.sh`


## Build and install manually

Open a terminal and enter the following commands:

`su root`

`pacman -S gcc sudo git #for arch linux based systems`

`apt update -y && apt install gcc sudo git #for debian based systems`

`exit`

`git clone https://github.com/mrybs/auto-install`

`cd auto-install`

`gcc -lstdc++ main.cpp -o bin/main`

`sudo mv bin/main /bin/autoinstall`


## How to run

To run autoinstall open a terminal and enter the following command:

`autoinstall`
