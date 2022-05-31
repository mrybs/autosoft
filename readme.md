Description
AutoInstall is a program under the GPL 3.0 license for quick installation of programs from repositories of systems based on Arch Linux, Debian and the like. Very convenient when reinstalling the system.

Build and install automatically
Open a terminal and enter the following commands
`{bash} {su root}«`
`{bash} {chmod +x install.sh}«`
`{bash} {./install.sh}«`

Build and install manually
Open a terminal and enter the following commands:
`{bash} {su root}«`
`{bash} {pacman -S gcc sudo git #for arch linux based systems}«`
`{bash} {apt update -y && apt install gcc sudo git #for debian based systems}«`
`{bash} {exit}«`
`{bash} {gcc -lstdc++ main.cpp -o bin/main}«`
`{bash} {sudo mv bin/main /bin/autoinstall}«`

How to run
To run autoinstall open a terminal and enter the following command
`{bash} {autoinstall}«`