#include "main.h"

long getFileLength (string filepath){ //Getting file lenght
    long i = 0;
    string cache; //Unuseless variable
    ifstream file(filepath);
    for (;getline(file, cache); i++); //Counting count of lines in the file
    return i;
}

string setPackageManager (){ //Setting packages manager
    string PACKAGEMANAGER = "";
    //Arch linux based 
    ifstream file1("/bin/pacman");
    ifstream file2("/bin/pacstrap");
    if (file1.is_open() && file2.is_open()) { //If pacman and pacstrap are in the system
        //Pacman or pacstrap
        string choice = "";
        bool man = false;
        cout << "If you using pacman write [Y]\nIf you using pacstrap write [N]\n# " ;
        cin >> choice; 
        string vars[12] = {"Y", "y", "yes", "Yes", "YEs", "YeS", "YES", "yEs", "yES", "yeS"}; //Variants of YES
        for(int i = 0; i < 12; i++){
            if(choice == vars[i]){
                man = true;
                break;}}
        if (man) PACKAGEMANAGER = "sudo pacman -Syy"; //Set pacman as default package manager
        if (!man){
            string root = "";
            cout << "Write root path\n# ";
            cin >> root;
            PACKAGEMANAGER = "sudo pacstrap " + root; //Using pacstrap as package manager
        }
    }else if (file1.is_open() && !file2.is_open()) //If only pacman is in the system
        PACKAGEMANAGER = "sudo pacman -Syy"; //Set pacman as default package manager
    else if (!file1.is_open() && file2.is_open()) { //If only pacstrap is in the system
        string root = "";
        cout << "Write root path\n# ";
        cin >> root;
        PACKAGEMANAGER = "sudo pacstrap " + root; //Using pacstrap as package manager
    }
    file1.close();
    file2.close();
    //Debian based
    ifstream file3("/bin/apt");
    ifstream file4("/bin/dpkg");
    if (file3.is_open()) //If dpkg and apt are in the system
        PACKAGEMANAGER = "sudo apt update -y && sudo apt install"; //Set apt as default package manager
    file3.close();
    file4.close();
    return PACKAGEMANAGER;
}