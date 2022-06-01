#include <iostream>
#include <string>
#include <fstream>
using namespace std;

void parse(string filepath);
long getFileLength(string filepath);
void setPackageManager();

string PACKAGEMANAGER = "";
long stFileLength = 0;
string* packages;
string* conflictPackages;

int main(){
    string st = "";
    string packagesToInstall;
    bool install = false;
    string choice = "";

    //system("clear");

    setPackageManager(); //Setting packages manager

    //system("clear");

    //Preparsing file
    cout << "Write *.st file name\n# "; //Getting filename
    cin >> st;
    ifstream file(st);
    if (!file.is_open()){
        cout << "\033[0;31mNo such file or directory, exit";
        return 1;
    }
   parse(st);

    //Parsing file and preinstalling packages
    for (int i = 0; i < stFileLength; i+=2){
        //Getting consent for the installation a group of packages
        system("clear");
        cout << "Are you sure to install " << packages[i] << "(" << packages[i+1] << ")? [y/n]\n# "; 
        cin >> choice; 
        string vars[12] = {"Y", "y", "yes", "Yes", "YEs", "YeS", "YES", "yEs", "yES", "yeS"}; //Variants of YES
        for (int i = 0; i < 12; i++){
            if (choice == vars[i]){
                install = true;
                break;}}
        if (install){
            packagesToInstall = packagesToInstall + packages[i+1] + "\n";
            cout << "YES.   ";
        }else{
            cout << "NO.    ";
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
    system("clear");
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
        system("clear");
        string command = (string)PACKAGEMANAGER + " " + packagesToInstall; 
        installResult = system(command.c_str());
        if(installResult == 0){system("clear"); cout << "\033[;32mDone.\n";} 
        else {cout << "\033[;31mError";}
    }
    return 0;
}

void parse(string filepath){
    stFileLength = getFileLength(filepath);
    string* results = new string[stFileLength];
    string* conflicts = new string[stFileLength];
    string line;
    ifstream file(filepath);
    for (int i = 0; getline(file, line); i++){
        const char * endOfLine = ";";
        string cache1 = line;
        string main;
    
        for (int k = 0; k < cache1.length(); k++)
            if (k != cache1.length())
                if (cache1[k] != *endOfLine) {main += cache1[k];}
                else break;
        results[i] = main;

        string cache2 = line;
        string::size_type pos2{};   // позиция разделителя в строке
        pos2 = cache2.find_first_of(endOfLine, pos2);  // ищем первый символ, начиная с pos = 0, являющийся разделителем
        cache2.erase(0, pos2+1); // удаляем все что перед найденным символом
        conflicts[i] = cache2;
    }
    file.close();
    packages = results;
}

long getFileLength(string filepath){ //Getting file lenght
    long i = 0;
    string cache; //Unuseless variable
    ifstream file(filepath);
    for (;getline(file, cache); i++);
    return i;
}

void setPackageManager(){ //Setting packages manager
    //Arch linux based 
    ifstream file1("/bin/pacman");
    ifstream file2("/bin/pacstrap");
    if (file1.is_open() && file2.is_open()) {
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
        if (man) PACKAGEMANAGER = "sudo pacman -Syy";
        if (!man){
            string root = "";
            cout << "Write root path\n# ";
            cin >> root;
            PACKAGEMANAGER = "sudo pacstrap " + root;
        }
    }else if (file1.is_open() && !file2.is_open()) {PACKAGEMANAGER = "sudo pacman -Syy";}
    else if (!file1.is_open() && file2.is_open()) {
        string root = "";
        cout << "Write root path\n# ";
        cin >> root;
        PACKAGEMANAGER = "sudo pacstrap " + root;
    }
    file1.close();
    file2.close();
    //Debian based
    ifstream file3("/bin/apt");
    if (file3.is_open()) PACKAGEMANAGER = "sudo apt update -y && sudo apt install";
    file3.close();
}