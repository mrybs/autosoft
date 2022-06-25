#include "main.h"

//Variables
string PACKAGEMANAGER = "";
string packagesToInstall;
bool* use;
string* name1;
string* packages1;
string* name2;
string* packages2;
long linesCount = 0;


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
    file.close();
    parse(st);
    if (DEBUG) cout << "File parced, no exceptions\n";
    //packages = confs -> packages1;

    //Parsing file and preinstalling packages
    for (int i = 0; i < linesCount/2; i++){
        if (DEBUG) cout << "The user having interview " << i << "/" << linesCount/2 <<"... \n";
        //Getting consent for the installation a group of packages
        cout << "Are you sure to install " << name1[i] << "(" << packages1[i] << ")? [y/n]\n# "; 
        cin >> choice; 
        string vars[12] = {"Y", "y", "yes", "Yes", "YEs", "YeS", "YES", "yEs", "yES", "yeS"}; //Variants of YES
        for (int k = 0; k < 12; k++)
            if (choice == vars[k]){
                install = true; break;}
        if (install){
            packagesToInstall = packagesToInstall + packages1[i] + "\n";
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
        if(DEBUG && installResult) cout << "The package manager did not returned code 0\n";
    }
    if (DEBUG) cout << "The program ended with code " << installResult << endl;
    return installResult;
}

void parse (string filepath){
    try{
        if (DEBUG) cout << "File parsing begins\n";
        

        if (DEBUG) cout << "File parsing 1 [";
        linesCount = getFileLength(filepath);
        packages1 = new string[linesCount/2+1];
        name1 = new string[linesCount/2];
        packages2 = new string[linesCount/2+1];
        name2 = new string[linesCount/2];
        use = new bool[linesCount/2];
        for(int i = 0; i < linesCount/2; ++i){
            packages1[i] = "";
            name1[i] = "";//SIGSEGV when i=3 (FIXED)
            packages2[i] = "";
            name2[i] = "";
            use[i] = false;
            if (DEBUG) cout << "#";
        }
        if (DEBUG) cout << "]\n";

        long j = 0;
        int i = 0;
        bool loob = true;
        //string cache = "";
        string line;
        ifstream file(filepath);

        while(getline(file, line)){
            i++;
            string cache1 = line;
            string cache2 = line;
            string main;
            for (int k = 0; k < cache1.length(); k++)
                if (cache1[k] != EOL) {main += cache1[k];}
                else break;
            if(loob){
                name1[j] = main;
            }else packages1[j] = main; //SIGSEGV when i=6 and loob=false
            
            string::size_type pos2{};
            pos2 = cache2.find_first_of(EOL, pos2);
            cache2.erase(0, pos2+1);
            if(loob) {name2[j] = cache2; j++;}
            if (DEBUG) {cout << "File parsing 2 - cycle " << i << "/" << linesCount << endl;/*cout << "LOL";*/}
            
            loob = !loob;
            
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

        for(int b = 0; b < linesCount/2; b++){
            if(name2[b] != "" && name2[b][0] != ' '){
               if(!use[b]){
                    while(true){
                        cout << "1) " << name1[b] << " conflicts with 2) " << name2[b] << "\nChoose one group [1/2]. " << 
                        "If you do not want to choose which of these, then write 3";
                        use[b] = true;
                        string choice;
                        cin >> choice;
                        if(atoi(choice.c_str()) <= 3 && atoi(choice.c_str()) >= 1){
                            cout << choice << ".     ";
                            if(atoi(choice.c_str()) == 1){
                                packagesToInstall = packagesToInstall + packages1[b] + " "; 
                            }else if(atoi(choice.c_str()) == 2){
                                packagesToInstall = packagesToInstall + packages2[b] + " ";
                            }
                            break;
                        }else cout << "You have selected a wrong value. Please, retry\n";
                    }
                }
            }
            if (DEBUG) cout << "File parsing 4 - cycle " << b+1 << "/" << linesCount/2 << endl;
        }
    }catch(std::exception e) {cout << "File parsing error";}
}