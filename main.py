import os
import re as regexp
import sys
import asconfig as config
import configparser as cp

install = config.INSTALL
update = config.UPDATE
remove = config.REMOVE

LANGUAGE = []

asfile = ""


def language(lang, langID):
    result = []
    for i in lang:
        result.append(i[langID])
    return result


def main():
    # Reading file
    global asfile
    if asfile == "":
        clear()
        asfile = input(LANGUAGE[7] + "\n>>> ")
    clear()
    file = open(asfile)
    find = regexp.search(r"AUTOSOFT:([\s\S]*):AUTOSOFT", open(asfile).read())
    if not file.readable():
        print(LANGUAGE[0], LANGUAGE[8] + " 10 " + LANGUAGE[16], sep="\n")
        sys.exit(10)
    if find is None:
        print(LANGUAGE[0], LANGUAGE[8] + " 11 " + LANGUAGE[16], sep="\n")
        sys.exit(11)
    text = file.read()

    # Simplifying file for parsing
    clear()
    text = comment(text.split("\n"), ";")
    text = removeOnLine(text.split("\n"), 0, sep=" ")
    text = removeOnLine(text.split("\n"), len(text.split("\n")) - 2, " ")
    if not (text.split("\n")[0] == "AUTOSOFT:" and text.split("\n")[len(text.split("\n")) - 2] == ":AUTOSOFT"):
        print(LANGUAGE[0], LANGUAGE[8] + " 20 " + LANGUAGE[16], sep="\n")
        sys.exit(20)
    text = removeOnLine(text.split("\n"), 0, sep="AUTOSOFT:")
    text = removeOnLine(text.split("\n"), len(text.split("\n")) - 2, ":AUTOSOFT")

    # Parsing file
    conditions = []
    allIDs = []
    for find in regexp.compile(r"\?\S*\s*[^!]*").findall(text):
        if find is None:
            print(LANGUAGE[0], LANGUAGE[8] + " 21 " + LANGUAGE[16], sep="\n")
            sys.exit(21)
        conditions.append(getConditionInfo(find))
    cconditions = conditions
    for i in conditions:
        allIDs.append(i[0])

    matches = findMatches(allIDs)

    # Asking user
    Install = ""
    Remove = ""
    popped = 0
    try:
        i = 0
        while i < len(conditions):
            currentMatchID = -1
            for j in matches:
                if j == conditions[i - 1][0]:
                    currentMatchID = j
                    break
            clear()
            if currentMatchID == -1:
                if conditions[i - 1][3] != [] and conditions[i][2] != []:
                    print(LANGUAGE[4] + " " + conditions[i - 1][1] + f" {LANGUAGE[14]}(+", end="")
                    print(*conditions[i - 1][2], sep=",", end="")
                    print("; -", end="")
                    print(*conditions[i - 1][3], sep=",", end="")
                    print(")? [Y/n]\n>>> ", end="")
                elif conditions[i - 1][3] != [] and conditions[i - 1][2] == []:
                    print(LANGUAGE[4] + " " + conditions[i - 1][1] + f" {LANGUAGE[14]}(-", end="")
                    print(*conditions[i - 1][3], sep=",", end="")
                    print(")? [Y/n]\n>>> ", end="")
                elif conditions[i - 1][3] == [] and conditions[i - 1][2] != []:
                    print(LANGUAGE[4] + " " + conditions[i - 1][1] + f" {LANGUAGE[14]}(+", end="")
                    print(*conditions[i - 1][2], sep=",", end="")
                    print(")? [Y/n]\n>>> ", end="")
                else:
                    print(LANGUAGE[4] + " " + conditions[i - 1][1] + LANGUAGE[14] + "? [Y/n]\n>>> ")
                entered = input().replace(" ", "")
                clear()
                if entered == "" or entered == "\n" or entered.lower() == "y" or entered.lower() == "yes":
                    for j in conditions[i - 1][2]:
                        Install += j + " "
                    for j in conditions[i - 1][3]:
                        Remove += j + " "
            else:
                matchesIDs = []
                matchesNames = []
                matchesInstall = []
                matchesRemove = []
                for j in range(0, len(conditions)):
                    if conditions[j][0] == currentMatchID:
                        matchesIDs.append(j)
                        matchesNames.append(conditions[j][1])
                        matchesInstall.append(conditions[j][2])
                        matchesRemove.append(conditions[j][3])
                for j in range(0, len(matchesNames)):
                    matchesNames[j] += "(" + str(j + 1) + ")"
                iMatchesNames = matchesNames
                matchesNames = []
                for j in range(0, len(iMatchesNames)-1):
                    matchesNames.append(iMatchesNames[j])
                clear()
                print(*matchesNames, sep=", ", end="")
                print(f" {LANGUAGE[27]} {iMatchesNames[len(matchesNames)]} {LANGUAGE[9]} {len(iMatchesNames)+1} {LANGUAGE[26]}")
                result = 1
                while True:
                    try:
                        result = int(input(LANGUAGE[13] + " [1-" + str(len(matchesIDs)+1) + "]\n>>> "))
                        if (result > 0 and result <= len(iMatchesNames)+1):
                            break
                        print(LANGUAGE[10])
                    except Exception as E:
                        print(LANGUAGE[11])
                if result != len(iMatchesNames)+1:
                    for j in matchesInstall[result-1]:
                        Install += j + " "
                    for j in matchesRemove[result-1]:
                        Remove += j + " "
                matches.pop(matches.index(currentMatchID))
                for j in range(0, len(matchesIDs)):
                    conditions.pop(matchesIDs[j] - popped)
                    popped += 1
            i += 1
    except KeyboardInterrupt as E:
        print(E)
    clear()
    iInstall = Install
    iRemove = Remove
    Install = ""
    Remove = ""
    for i in range(0, (len(iInstall.split(" ")))):
        if iInstall.split(" ")[i] != "":
            if i != len(iInstall.split(" ")) - 1 and i != len(iInstall.split(" ")) - 2:
                Install += iInstall.split(" ")[i] + " "
            else:
                Install += iInstall.split(" ")[i]
    for i in range(0, (len(iRemove.split(" ")))):
        if iRemove.split(" ")[i] != "":
            if i != len(iRemove.split(" ")) -1 and i != len(iRemove.split(" ")) -2:
                Remove += iRemove.split(" ")[i] + " "
            else:
                Remove += iRemove.split(" ")[i]
    if Remove != "" and Install != "":
        print(LANGUAGE[4] + " ", end="")
        print(*Install.split(" "), sep=", ", end="")
        print(f" {LANGUAGE[14]} {LANGUAGE[6]} ", end="")
        print(*Remove.split(" "), sep=", ", end="")
        print(f" {LANGUAGE[15]}? [Y/n]\n>>> ", end="")
    elif Remove != "" and Install == "":
        print(LANGUAGE[5] + " ", end="")
        print(*Remove.split(" "), sep=", ", end="")
        print(f" {LANGUAGE[15]}? [Y/n]\n>>> ", end="")
    elif Remove == "" and Install != "":
        print(LANGUAGE[4] + " ", end="")
        print(*Install.split(" "), sep=", ", end="")
        print(f" {LANGUAGE[14]}? [Y/n]\n>>> ", end="")
    else:
        print(LANGUAGE[12], sep="\n")
        sys.exit(31)
    entered = input().replace(" ", "")
    clear()
    if entered == "" or entered == "\n" or entered.lower() == "y" or entered.lower() == "yes":
        os.system(update)
        clear()
        for i in Remove.split(" "):
            clear()
            if i != "":
                os.system(remove + " " + i)
            clear()
        clear()
        if install != "":
            os.system(install + " " + Install)
        clear()
        sys.exit(40)
    clear()
    sys.exit(0)


def configuration():
    global LANGUAGE
    l = 0
    cfg = cp.ConfigParser()
    cfg.read("settings.ini")
    while(True):
        try:
            print("Choose language")
            print()
            for i in range(0, len(config.LANGUAGE[0])):
                print(str(i + 1) + ") " + config.LANGUAGE[len(config.LANGUAGE) - 1][i])
            l = int(input("\n>>> "))
            if l > 0 and l < len(config.LANGUAGE[0])+1:
                break
            else:
                l = 0
                clear()
                print(LANGUAGE[10])
        except Exception as E:
            clear()
            print(LANGUAGE[11])
    cfg["SETTINGS"]["language"] = str(l-1)
    LANGUAGE = language(config.LANGUAGE, l-1)
    clear()
    entered = input(LANGUAGE[17] + "?\n>>> ").replace(" ", "")
    if entered == "" or entered == "\n" or entered.lower() == "y" or entered.lower() == "yes":
        cfg["SETTINGS"]["clear"] = "true"
        clear()
        print(f"\n{LANGUAGE[23]}\n")
    else:
        cfg["SETTINGS"]["clear"] = "false"
        print(f"\n{LANGUAGE[24]}\n")
    with open("settings.ini", 'w') as configfile:
        cfg.write(configfile)


def helpPrint():
    clear()
    print(f"{LANGUAGE[21]}\n\n\n"
          f"$ python main.py                      -   {LANGUAGE[18]}\n\n"
          f"$ python main.py --as2 path/to/.as2   -   {LANGUAGE[19]}\n\n"
          f"$ python main.py --config             -   {LANGUAGE[20]}\n\n"
          f"$ python main.py --help               -   {LANGUAGE[22]}\n\n")


def clear():
    cfg = cp.ConfigParser()
    cfg.read("settings.ini")
    if cfg["SETTINGS"]["clear"] == "true":
        os.system("clear")


def findMatches(list):
    return [x for i, x in enumerate(list) if x in list[:i]]


def getConditionInfo(text):
    Install = []
    Remove = []
    text = text.replace("\t", "")
    otext = text
    result = []
    find = regexp.search("(\\?\\d+ as \"(\\S|\\s)+?\")", text)
    clear()
    if find is None:
        print(LANGUAGE[0], LANGUAGE[8] + " 23 " + LANGUAGE[16], sep="\n")
        sys.exit(23)
    text = find.group()
    text = text.replace("?", "")
    find = regexp.search("\\d+", text)
    result.append(int(find.group()))
    text = text.replace(find.group(), "")
    text = text.replace(" as \"", "")
    text = text.replace("\"", "")
    result.append(text)

    itext = ""
    for i in range(1, len(otext.split("\n"))-1):
        itext += otext.split("\n")[i] + "\n"
    for i in itext.split("\n"):
        if i.find("Install ") == 0:
            i = i.replace("Install ", "")
            i = i.replace(" ", "")
            clear()
            if i == "":
                print(LANGUAGE[0], LANGUAGE[8] + " 24 " + LANGUAGE[16], sep="\n")
                sys.exit(24)
            Install.append(i)
        elif i.find("Remove ") == 0:
            i = i.replace("Remove ", "")
            i = i.replace(" ", "")
            clear()
            if i == "":
                print(LANGUAGE[0], LANGUAGE[8] + " 24 " + LANGUAGE[16], sep="\n")
                sys.exit(24)
            Remove.append(i)
    result.append(Install)
    result.append(Remove)
    return result


def comment(lines, string):
    text = ""
    for i in lines:
        j = True
        for k in i:
            if j:
                if k is string or k == "\n":
                    j = False
                else:
                    text += k
        text += "\n"
    return text


def removeOnLine(lines, id, sep=" "):
    lines[id] = lines[id].replace(sep, "")
    result = ""
    for i in range(0, len(lines) - 1):
        if lines[i] == "":
            continue
        result += (lines[i] + "\n")
    return result


if __name__ == "__main__":
    try:
        cfg = cp.ConfigParser()
        cfg.read("settings.ini")
        try:
            LANGUAGE = language(config.LANGUAGE, int(cfg["SETTINGS"]["language"]))
        except Exception as E:
            if len(config.LANGUAGE):
                if len(config.LANGUAGE[0]):
                    LANGUAGE = language(config.LANGUAGE, 0)
                else:
                    sys.exit(127)
            else:
                sys.exit(127)
        if len(sys.argv) == 2 and sys.argv[1] == "--config":
            configuration()
        elif len(sys.argv) == 3 and sys.argv[1] == "--as2":
            asfile = sys.argv[2]
            main()
        elif len(sys.argv) == 2 and sys.argv[1] == "--help":
            helpPrint()
        elif len(sys.argv) == 4 and sys.argv[1] == "--as2" and sys.argv[3] == "--config":
            asfile = sys.argv[2]
            main()
            configuration()
        elif len(sys.argv) == 4 and sys.argv[1] == "--config" and sys.argv[2] == "--as2":
            asfile = sys.argv[3]
            configuration()
            main()
        else:
            main()
    except KeyboardInterrupt as KI:
        clear()
        sys.exit(0)