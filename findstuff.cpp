#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <iostream>
#include <dirent.h>

using namespace std;

DIR *dir;
    struct dirent *dp;
    

void fileInDir(char* name, char* path);

void fileInSub(char* name, char* path);

void findStringInDir(char* string, char* path);

int getFilesInSub( int &i, char** list, char* path);

void getFilesInDir(char** list, char* path);

char** filterFileType(char** list, char* type);

int main(){

    
char path[1000];

getcwd(path,sizeof(path));

    //TODO scan in input

    // char * input = "find file.txt";

    //fileInDir("file.txt");

    // fileInSub("underFile.txt", path);

    // findStringInDir("hello", path );

    char* list[1000];
    int i = 0;
    // getFilesInSub(i, list, path);
    getFilesInSub( i,list, path);

    filterFileType(list, "txt");

}



char** filterFileType(char** list, char* type){
    char curr[1000];
    char* filtered[1000];
    int fIndex = 0;
    int last;
    int end;
    for(int i = 0; list[i] != NULL; i++){
        last = strlen(type)-1;
        end = strlen(list[i])-1;
        while(list[i][end] == type[last]){
            
            end -= 1;
            last -= 1;
           
        }
        if(last == -1){
            filtered[fIndex] = list[i];
            fIndex += 1;
        }
    }

    cout << "\n\nhere is filtered list of " << type << " files:" << endl;
    for(int i = 0; i < fIndex; i++){
        cout << filtered[i] << endl;
    }

    return filtered;
}


//TODO make list of children 


// look for word in current directory
void findStringInDir(char* string, char* path){

    int index = 0;
    char* list[1000];
    char* loc[1000];


      DIR *local;
    local = opendir(path);
                while ((dp = readdir(local)) != NULL)
                {
                  // try to open file
                  FILE *file = fopen(dp->d_name, "r");
                  
int arr_size = 1000;
                  char content[arr_size];

                  for(int i = 0; i < arr_size; i ++){
                      content[i] = 0;
                  }
                  
                    fread(content, arr_size, 1, file);
 int sIndex = 0;
                        int size = strlen(string);
                        // cout << string << " size is " << size << endl;

                    for(int i = 0; i < arr_size; i++){
                        
                       
                        if(content[i] == string[sIndex]){
                            sIndex ++;
                            // cout << sIndex <<" " << content[i+1] << " " << string[sIndex] <<endl;
                            if(sIndex+1 == size){
                                // cout << "found file " << dp->d_name << strlen(content)<<  endl;
                                
                                list[index] = dp->d_name;
                                loc[index] = path;
                                index += 1;
                            }
                        } else{
                            sIndex = 0;
                        }

                    }

                    // cout << content << endl;
                 
                    //     if(dp->d_type == DT_REG) cout << "type: file" << endl;
                    //     else cout << "type: folder" << endl;
                }
                cout << "found '" << string << "' in the following files" << endl;
                for(int i = 0; i < index; i++){

                    //TODO include location
                    cout << list[i] << " location: " << loc[i] << endl;
                }

}

int getFilesInSub( int &i, char** list, char* path){

    DIR *local;

    
    int isOG = i;

    local = opendir(path);
    // if(dir == NULL) {
    //     return;
    // }
     while ((dp = readdir(local)) != NULL)
                {

                    if(dp->d_type == DT_REG){

                        list[i] = dp->d_name;
                        i +=1;
                    }



                    if(strcmp(dp->d_name, "..") != 0 && strcmp(dp->d_name, ".") != 0 && dp->d_type != DT_REG){

                    // cout << "d name is " << dp->d_name << endl;
                    char possPath[100];
                    strcpy(possPath, path);
                    strcat(possPath, "/");
                    strcat(possPath, dp->d_name);
                    if(  opendir(possPath) != NULL){
                        // cout << "possible path is " << possPath << endl;
                        getFilesInSub(i, list, possPath);
                        
                    }
                    }
                    //     if(dp->d_type == DT_REG) cout << "type: file" << endl;
                    //     else cout << "type: folder" << endl;
                }

                if(isOG == 0){
                    for(int j =0; j < i; j++){
                        cout << list[j] << endl;
                    }
                }
            
return i;
}

void getFilesInDir(char** list, char* path){





int i = 0;

DIR *local;
    local = opendir(path);
    while ((dp = readdir(local)) != NULL)
                {
                    // ensure regular file
                    if(dp->d_type == DT_REG){
                        // cout << dp->d_name << endl;
                        // char full_path [1000];
                        // strcpy(full_path, path);
                        // strcat(full_path, "/");
                        // strcat(full_path, dp->d_name);
                        list[i] = dp->d_name;
                        i += 1;
                    }
                    
                }

        for(int num = 0; num< i; num++){
            cout << list[num] << endl;
        }


}




// not needed anymore


// checks current directory for file
void fileInDir(char* name, char* path){
    DIR *local;
    local = opendir(path);
    while ((dp = readdir(local)) != NULL)
                {
                    if(strcmp(name , dp->d_name) == 0){
                        cout << "found the file!" << endl;
                        return;
                    }
                 
                    //     if(dp->d_type == DT_REG) cout << "type: file" << endl;
                    //     else cout << "type: folder" << endl;
                }
            

            cout << "file not here" << endl;
                // rewinddir(dir);
                // closedir(dir);

}

// Checks all the subdirectories for file
void fileInSub(char* name, char* path){

    DIR *local;

    local = opendir(path);
    // if(dir == NULL) {
    //     return;
    // }
     while ((dp = readdir(local)) != NULL)
                {

                    cout << "checking " << dp->d_name << endl;
                    if(strcmp(name , dp->d_name) == 0){
                        cout << "found the file!" << endl;
                        return;
                    }
                    if(strcmp(dp->d_name, "..") != 0 && strcmp(dp->d_name, ".") != 0){

                    // cout << "d name is " << dp->d_name << endl;
                    char possPath[100];
                    strcpy(possPath, path);
                    strcat(possPath, "/");
                    strcat(possPath, dp->d_name);
                    if(  opendir(possPath) != NULL){
                        cout << "possible path is " << possPath << endl;
                        fileInSub(name, possPath);
                        
                    }
                    }
                    //     if(dp->d_type == DT_REG) cout << "type: file" << endl;
                    //     else cout << "type: folder" << endl;
                }
            

}

