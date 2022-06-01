#include "main.h"

//Variables
string PACKAGEMANAGER = "";
long stFileLength = 0;
string* packages;
string* conflicts;
string* markedConflicts;

int main (){
    string st = "";
    string packagesToInstall;
    bool install = false;
    string choice = "";

    //CLEAR;

    PACKAGEMANAGER = setPackageManager(); //Setting packages manager

    //CLEAR;

    //Preparsing file
    cout << "Write *.st file name\n# "; //Getting filename
    cin >> st;
    ifstream file(st);
    if (!file.is_open()){
        cout << "\033[0;31mNo such file or directory, exit";
        return 1;
    }
    preparse(st);

    //Parsing file and preinstalling packages
    markedConflicts = new string[stFileLength];
    for (int i = 0; i < stFileLength; i+=2){

        for(int k = 0; k < stFileLength; k++){
            if(conflicts[k] != "" && conflicts[k][0] != ' ' && markedConflicts[k] != conflicts[k] 
            && markedConflicts[k] != packages[i] && packages[i] != ""){
                while(true){
                    try{
                        cout << "(1)" << packages[k] << " conflicts with (2)" << conflicts[k] << "\n";
                        markedConflicts[i] = packages[k];
                        string choice;
                        cout << "Select one package group(number), that you want to install. If you do not want to install these " << 
                        "packages, select 3.\n# ";
                        cin >> choice;
                        if(atoi(choice.c_str()) <= 3 && atoi(choice.c_str()) >= 1){
                            cout << choice << ".     ";
                            if(atoi(choice.c_str()) == 1){
                                packagesToInstall = packagesToInstall + packages[i+1] + "\n";
                                packages[i] = "";
                                conflicts[k] = "";
                            }else if(atoi(choice.c_str()) == 2){
                                packagesToInstall = packagesToInstall + conflicts[k+1] + "\n";
                                packages[i] = "";
                                conflicts[k] = "";
                            }else {
                                packages[i] = "";
                                conflicts[k] = "";
                            }
                            break;
                        }else cout << "You have selected a wrong value. Please, retry\n";
                    } catch(exception e){
                        cout << "You have not selected a number. Please, retry\n";
                    }
                }
            }
        }
        //Getting consent for the installation a group of packages
        CLEAR;
        if(packages[i] != ""){
            cout << "Are you sure to install " << packages[i] << "(" << packages[i+1] << ")? [y/n]\n# "; 
            cin >> choice; 
            string vars[12] = {"Y", "y", "yes", "Yes", "YEs", "YeS", "YES", "yEs", "yES", "yeS"}; //Variants of YES
            for (int k = 0; k < 12; k++)
                if (choice == vars[k]){
                    install = true; break;}
            if (install){
                packagesToInstall = packagesToInstall + packages[i+1] + "\n";
                cout << "YES.   ";
            }else cout << "NO.    ";
        }
        install = false;
    }
    size_t pos = 0;
    while ((pos = packagesToInstall.find("\n", pos)) != string::npos ) packagesToInstall.replace(pos, 1, " ");
    if (packagesToInstall == ""){
        system("clear");
        cout << "\n\033[0;31mUser did not select the packages to install, exit";
        return 2;
    }
    CLEAR;
    cout << "Are you sure to install these packages: " << packagesToInstall << "? [y/n]\n# ";
    cin >> choice;
        string vars[12] = {"Y", "y", "yes", "Yes", "YEs", "YeS", "YES", "yEs", "yES", "yeS"}; //Variants of YES
        for(int i = 0; i < 12; i++){
            if(choice == vars[i]){
                install = true;
                break;}}

    int installResult = 0;

    //Installing packages
    if (install) {
        CLEAR;
        string command = (string)PACKAGEMANAGER + " " + packagesToInstall; 
        installResult = system(command.c_str());
        if(installResult == 0){CLEAR; cout << "\033[;32mDone.\n";} 
        else {cout << "\033[;31mError";}
    }
    return 0;
}

void preparse (string filepath){
    stFileLength = getFileLength(filepath);
    packages = new string[stFileLength];
    conflicts = new string[stFileLength];
    string line;
    ifstream file(filepath);
    for (int i = 0; getline(file, line); i++){
        const char * endOfLine = ";";
        string cache1 = line;
        string main;
    
        for (int k = 0; k < cache1.length(); k++)
            if (k != cache1.length()){
                if (cache1[k] != *endOfLine) {main += cache1[k];}
                else break;}
        packages[i] = main;

        string cache2 = line;
        string::size_type pos2{};
        pos2 = cache2.find_first_of(endOfLine, pos2);
        cache2.erase(0, pos2+1);
        conflicts[i] = cache2;
    }
    file.close();
}