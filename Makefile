res: main.py
	bash -c 'echo "#!/bin/python" > /usr/bin/autosoft && cat main.py >> /usr/bin/autosoft && echo "#!/bin/python" > /usr/bin/asconfig.py && cat asconfig.py >> /usr/bin/asconfig.py && chmod +x /usr/bin/autosoft || printf "\033[0;31mCritical error\033[0m: Failed to install AutoSoft\n\n" && exit'
