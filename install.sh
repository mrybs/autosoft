#!/bin/bash
clear

#----------------------#
#---Created by mrybs---#
#---GitHub: /mrybs/----#
#---License: GPL-3.0---#
#----------------------#

printf "\033[0;35m" #sets magneta foreground color

printf "#----------------------#\n"
printf "#---Created by mrybs---#\n"
printf "#---GitHub: /mrybs/----#\n"
printf "#---License: GPL-3.0---#\n"
printf "#----------------------#\n\n"

printf "\033[0m" #sets default color

whoami="$(whoami)"

if [[ "$whoami" = "root" ]]; then
        echo "#!/bin/python" > /usr/bin/autosoft && cat main.py >> /usr/bin/autosoft && echo "#!/bin/python" > /usr/bin/asconfig.py && cat asconfig.py >> /usr/bin/asconfig.py && chmod +x /usr/bin/autosoft || printf "\033[0;31mCritical error\033[0m: Failed to install AutoSoft\n\n" || exit

        printf "\nWrite\n\n$ \033[0;35mautosoft\033[0m\n\nto run program\n\n"
else
    printf "\033[0;31mCritical error\033[0m: $whoami user cannot install the AutoSoft. \nLaunch the installer on behalf on the super-user\n\n"
fi
