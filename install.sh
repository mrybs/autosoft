#!/bin/bash
clear

printf "#----------------------#\n"
printf "#---Created by mrybs---#\n"
printf "#---GitHub: /mrybs/----#\n"
printf "#---License: GPL-3.0---#\n"
printf "#----------------------#\n\n"

printf "\033[0m" #sets default color

whoami="$(whoami)"

if [[ "$whoami" = "root" ]]; then
        pacman -V && pacman -Sy python || printf "\033[0;31mCritical error\033[0m: Failed to install python.\n\n" && exit
        apt -v && apt-get update -y && apt-get install build-essential zlib1g-dev libncurses5-dev libgdbm-dev libnss3-dev libssl-dev libreadline-dev libffi-dev libsqlite3-dev wget libbz2-dev && mkdir /.install && cd /.install && wget https://www.python.org/ftp/python/3.10.0/Python-3.10.0rc2.tgz && tar -xf Python-3.10.*.tgz && cd Python-3.10.0rc2 && ./configure --enable-optimizations && make -j 4 && sudo make altinstall || printf "\033[0;31mCritical error\033[0m: Failed to install python.\n\n" && exit
        python -V || printf "\033[0;31mCritical error\033[0m: Failed to install python.\n\n" && exit
        echo "#!/bin/python" > /usr/bin/autosoft && cat main.py >> /usr/bin/autosoft && echo "#!/bin/python" > /usr/bin/asconfig.py && cat asconfig.py >> /usr/bin/asconfig.py && chmod +x /usr/bin/autosoft || printf "\033[0;31mCritical error\033[0m: Failed to install AutoSoft\n\n" && exit

        printf "\nWrite\autosoft\n for run program\n\n"
else
    printf "\033[0;31mCritical error\033[0m: $whoami user cannot install the BashCusomiser. \nLaunch the installer on behalf on the super-user\n\n"
fi
