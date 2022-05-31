#!/bin/bash

#----------------------#
#---Created by mrybs---#
#---GitHub: /mrybs/----#
#---License: GPL-3.0---#
#----------------------#

printf "\033[0;35m" #sets magneta foreground color

clear

printf "#----------------------#\n"
printf "#---Created by mrybs---#\n"
printf "#---GitHub: /mrybs/----#\n"
printf "#---License: GPL-3.0---#\n"
printf "#----------------------#\n\n"

printf "\033[0m" #sets default color

whoami="$(whoami)"

if [[ "$whoami" = "root" ]]; then
    #pacman (arch)
        pacman -Sy gcc sudo git
        clear

    #apt-get (debian)
        apt-get update -y
        apt-get install gcc sudo git
        clear 

        printf "#----------------------#\n"
        printf "#---Created by mrybs---#\n"
        printf "#---GitHub: /mrybs/----#\n"
        printf "#---License: GPL-3.0---#\n"
        printf "#----------------------#\n\n"

        printf "\033[0m" #sets default color

        gcc -lstdc++ main.cpp -o bin/main

    mv bin/main /bin/autoinstall
    printf "\nWrite\nautoinstall\nfor run program\n\n"
else
    printf "\033[0;31mCritical error\033[0m:  user cannot install the AutoInstall. \nLaunch the installer on behalf on the super-user\n\n"
fi
