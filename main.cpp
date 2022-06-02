#include "main.h"

//Variables
string PACKAGEMANAGER = "";
long stFileLength = 0;
//string* packages;
//string* conflicts;
//string* markedConflicts;
//conflicts* confs = new conflicts();
string packagesToInstall;
bool* use;
//string dataed;
string* name1;
string* packages1;
string* name2;
string* packages2;

/*long stringLinesCounter(string str){
    try{
        long l = 0;
        size_t pos = 0;
        while ((pos = dataed.find("\n")) != string::npos) {l++;}
        return l;
    }catch(std::exception e){
        cout << "SLC error";
    }
    return 0;
}*/


int main (){
    string st = "";
    bool install = false;
    string choice = "";

    CLEAR;

    PACKAGEMANAGER = setPackageManager(); //Setting packages manager

    CLEAR;

    //Preparsing file
    cout << "Write *.st file name\n# "; //Getting filename
    cin >> st;
    ifstream file(st);
    if (!file.is_open()){
        cout << "\033[0;31mNo such file or directory, exit";
        return 1;
    }
    stFileLength = getFileLength(st);
    file.close();
    parse(st);
    //packages = confs -> packages1;

    //Parsing file and preinstalling packages
    for (int i = 0; i < stFileLength/2; i+=2){
        
        //Getting consent for the installation a group of packages
        if(packages1[i] != ""){
            cout << "Are you sure to install " << packages1[i] << "(" << packages1[i+1] << ")? [y/n]\n# "; 
            cin >> choice; 
            string vars[12] = {"Y", "y", "yes", "Yes", "YEs", "YeS", "YES", "yEs", "yES", "yeS"}; //Variants of YES
            for (int k = 0; k < 12; k++)
                if (choice == vars[k]){
                    install = true; break;}
            if (install){
                packagesToInstall = packagesToInstall + packages1[i+1] + "\n";
                cout << "YES.   ";
            }else cout << "NO.    ";
        }
        install = false;
    }
    size_t pos = 0;
    while ((pos = packagesToInstall.find("\n", pos)) != string::npos ) packagesToInstall.replace(pos, 1, " ");
    if (packagesToInstall == ""){
        CLEAR;
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

void parse (string filepath){
    try{
        
        long linesCount = getFileLength(filepath);

        
        long i = 0;

        packages1 = new string[linesCount/2];
        name1 = new string[linesCount/2];
        packages2 = new string[linesCount/2];
        name2 = new string[linesCount/2];
        use = new bool[linesCount/2];
        for(int i = 0; i < linesCount/2; i++){
            packages1[i] = "";
            name1[i] = "";
            packages2[i] = "";
            name2[i] = "";
            use[i] = false;
        }

        long j = 0;
        //dataed = ""; 
        string cache = "";
        string line;
        ifstream file(filepath);

        while(getline(file, cache)){ 
            //dataed += cache;
             string cache1 = line;
            string main;
        
            for (int k = 0; k < cache1.length(); k++)
                if (cache1[k] != EOL) {main += cache1[k];}
                else break;
            if(i%2==1){
                name1[j] = main;
            }else packages1[j] = main;

            string cache2 = line;
            string::size_type pos2{};
            pos2 = cache2.find_first_of(EOL, pos2);
            cache2.erase(0, pos2+1);
            if(i%2==1) {name2[j] = cache2; j++;}
            i++;
            cout << "ping - ";
        }


        for(int i = 0; i < linesCount/2; i++){
            for(int k = 0; k < linesCount/2; k++){
                if(name1[i] == name2[k]){
                    packages2[k] = packages1[i];
                    use[k] = true;
                }
            }
        }

        for(int i = 0; i < linesCount/2; i++){
            if(name2[i] != "" && name2[0] != " "){
                if(!use[i]){
                    cout << "1) " << name1[i] << " conflicts with 2) " << name2[i] << "\nChoose one group [1/2]. " << 
                    "If you do not want to choose which of these, then write 3";
                    use[i] = true;
                    string choice;
                    cin >> choice;
                    if(atoi(choice.c_str()) <= 3 && atoi(choice.c_str()) >= 1){
                        cout << choice << ".     ";
                        if(atoi(choice.c_str()) == 1){
                            packagesToInstall = packagesToInstall + packages1[i] + "\n";
                        }else if(atoi(choice.c_str()) == 2){
                            packagesToInstall = packagesToInstall + packages2[i] + "\n";
                        }else {
                        }
                        break;
                    }else cout << "You have selected a wrong value. Please, retry\n";
                }
            }
        }
    }catch(std::exception e) {cout << "parce error";}
}