#include "main.h"

//Variables
string PACKAGEMANAGER = "";
long stFileLength = 0;
string packagesToInstall;
bool* use;
string* name1;
string* packages1;
string* name2;
string* packages2;


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
        cout << "\033[0;31mNo such file or directory, exit\n";
        if (DEBUG) cout << "The program ended with code 1";
        return 1;
    }
    stFileLength = getFileLength(st);
    file.close();
    parse(st);
    if (DEBUG) cout << "File parced, no exceptions\n";
    //packages = confs -> packages1;

    //Parsing file and preinstalling packages
    for (int i = 0; i < stFileLength/2; i+=2){
        if (DEBUG) cout << "The user having interview " << i << "... \n";
        //Getting consent for the installation a group of packages
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
        install = false;
    }
    if (DEBUG) cout << "The user has interviewed\n";

    size_t pos = 0;
    while ((pos = packagesToInstall.find("\n", pos)) != string::npos ) packagesToInstall.replace(pos, 1, " ");
    if (packagesToInstall == ""){
        CLEAR;
        cout << "\n\033[0;31mUser did not select the packages to install, exit";
        if (DEBUG) cout << "The program ended with code 2";
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
        else {cout << "\033[;31mError\n";}
        if(DEBUG) cout << "The package manager did not returned code 0\n";
    }
    if (DEBUG) cout << "The program ended with code " << installResult << endl;
    return installResult;
}

void parse (string filepath){
    try{
        if (DEBUG) cout << "File parsing begins\n";
        long linesCount = getFileLength(filepath);
        long i = 0;

        if (DEBUG) cout << "File parsing 1 [";
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
            if (DEBUG) cout << "#";
        }
        if (DEBUG) cout << "]\n";

        long j = 0;
        i = 0;
        string cache = "";
        string line;
        ifstream file(filepath);

        while(getline(file, cache)){ 
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
            if (DEBUG) cout << "File parsing 2 - cycle " << i << "/" << linesCount << endl;
        }


        for(int g = 0; g < linesCount/2; g++){
            for(int k = 0; k < linesCount/2; k++){
                if(name1[g] == name2[g]){
                    packages2[k] = packages1[g];
                    use[k] = true;
                    if (DEBUG) cout << "File parsing 3 - cycle " << g+1 << "-" << k+1 << "/" << linesCount/2 << "-" << linesCount/2 << endl;
                }
            }
        }

        for(int g = 0; g< linesCount/2; g++){
            if(name2[g] != "" && name2[0] != " "){
                if(!use[g]){
                    while(true){
                        cout << "1) " << name1[g] << " conflicts with 2) " << name2[g] << "\nChoose one group [1/2]. " << 
                        "If you do not want to choose which of these, then write 3";
                        use[g] = true;
                        string choice;
                        cin >> choice;
                        if(atoi(choice.c_str()) <= 3 && atoi(choice.c_str()) >= 1){
                            cout << choice << ".     ";
                            if(atoi(choice.c_str()) == 1){
                                packagesToInstall = packagesToInstall + packages1[g] + "\n";
                            }else if(atoi(choice.c_str()) == 2){
                                packagesToInstall = packagesToInstall + packages2[g] + "\n";
                            }else {
                            }
                            break;
                        }else cout << "You have selected a wrong value. Please, retry\n";
                    }
                }
            }
            if (DEBUG) cout << "File parsing 4 - cycle " << g+1 << "/" << linesCount/2 << endl;
        }
    }catch(std::exception e) {cout << "File parsing error";}
}