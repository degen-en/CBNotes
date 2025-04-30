#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char text[4096]; // <--- avaible text in note
    char name[32]; // <-- avaible name length
    char style;

    int tarId[512];
} Note;

int notesLen=2;

Note notes[65536]; // <--- number of avaible notes

// DO NOT change if you don't want loose your notes ^

int currId = 0;

int findLengthBeforeZero(int arr[]);
int findLengthBeforeZeroNote(Note arr[]);
int* removeRepeatingTargets(Note arr[], int id);
int findIdByName(char name[], char tar);
void commands();

void saveToFile(const char *filename);
void loadFromFile(const char *filename);



int main() {
    
    strcpy(notes[0].name, "/");
    
    loadFromFile("notes.dat");

    while(1){

    
    int tarLen = findLengthBeforeZero(notes[currId].tarId);
    for (int i =0;i<tarLen;i++){
        
        if (notes[notes[currId].tarId[i]].name[0] == '.')
        {
            //printf(" it doesn't exist ");
            continue;
        }
        printf("\033[1;%dm%s \033[1;0m", notes[notes[currId].tarId[i]].style, notes[notes[currId].tarId[i]].name);
    }
    printf("\n");
    
    commands();
    saveToFile("notes.dat");
    }

}






void commands(){
    printf("-\033[1;%dm%s \033[1;0m$ ", notes[currId].style, notes[currId].name);
    char command[32];
    scanf("%s", &command);
    getchar();

    if (!strcmp(command, "cat")){
        printf("\n");
        char name[32]; scanf("%s",&name);
        int id;
        if (strcmp(name, ".")){
            id = findIdByName(name, 'i');
        }else{
            id = currId;
        }
        if (id == -1){
            printf("%s\n", "not found in note");
            return;
        }
        printf("%s\n", notes[id].text);
        return;
    }

    if (!strcmp(command, "mk")){
        //printf("\n");
        char name[32]; scanf("%s",&name);
        int id = findIdByName(name, 'o');
        if (id != -1){
            printf("%s\n", "already exists!");
            return;
        }
        
        int emptySpace = findLengthBeforeZeroNote(notes);
        strcpy(notes[emptySpace].name, name);
        
        int len =findLengthBeforeZero(notes[currId].tarId);
        notes[currId].tarId[len] = emptySpace;
        len = findLengthBeforeZero(notes[emptySpace].tarId);
        notes[emptySpace].tarId[len] = currId;
        
        // notes[currId].tarId = removeRepeatingTargets(notes, currId);   // must be modifiable lvalue" 
        // notes[emptySpace].tarId = removeRepeatingTargets(notes, emptySpace);

        notesLen++;

        return;
    }

    if (!strcmp(command, "cd")){
        char name[32]; scanf("%s",&name);
        int id = findIdByName(name, 'i');
        if (id == -1){
            printf("%s\n", "not found in note");
            return;
        }
        currId = id;
        return;
    }
    if (!strcmp(command, "gcd")){
        char name[32]; scanf("%s",&name);
        int id = findIdByName(name, 'o');
        if (id == -1){
            printf("%s\n", "not found");
            return;
        }
        currId = id;
        return;
    }

    if (!strcmp(command, "cg")){
        char name[32]; scanf("%s",&name);
        getchar();
        int id;
        if (strcmp(name, ".")){
            id = findIdByName(name, 'i');
        }else{
            id = currId;
        }
        
        if (id == -1){
            printf("%s\n", "not found in note");
            return;
        }
        
        fgets(notes[id].text, 4096, stdin);
        //scanf("%s", );
        
        return;
    }
    if (!strcmp(command, "cgs")){
        char name[32]; scanf("%s",&name);
        getchar();
        int id;
        if (strcmp(name, ".")){
            id = findIdByName(name, 'i');
        }else{
            id = currId;
        }
        if (id == -1){
            printf("%s\n", "not found in note");
            return;
        }
        
        scanf("%d", &notes[id].style);
        
        return;
    }



    if (!strcmp(command, "rmnote")){
        char name[32]; scanf("%s",&name);
        int id;
        if (strcmp(name, ".")){
            id = findIdByName(name, 'i');
        }else{
            id = currId;
        }
        if (id == -1){
            printf("%s\n", "not found");
            return;
        }

        int len = findLengthBeforeZero(notes[id].tarId);
        for (int i=0;i<len;i++){
            notes[id].tarId[i] = -1;
        }

        // for(int i =512; i > 0; i--){
        //     notes[id].tarId[i] = 0;
        // }

        notes[id].text[0] = '\0';
        notes[id].style = 0;
        notes[id].name[0] = '.';
        notes[id].name[1] = '!';
        //notes[id].name[2] = deletedNotes+48;
        
        
        return;
    }


    if (!strcmp(command, "rm")){
        char name[32]; scanf("%s",&name);
        int id;
        if (strcmp(name, ".")){
            id = findIdByName(name, 'i');
        }else{
            id = currId;
        }
        if (id == -1){
            printf("%s\n", "not found in note");
            return;
        }
        notes[id].text[0] = '\0';
    }
    if (!strcmp(command, "fmk")){
        //printf("\n");
        char name[32]; scanf("%s",&name);
        int id = findIdByName(name, 'o');
        if (id != -1){
            printf("%s\n", "already exists!");
            return;
        }
        int emptySpace = findLengthBeforeZeroNote(notes);
        strcpy(notes[emptySpace].name, name);
        int len =findLengthBeforeZero(notes[currId].tarId);
        //notes[currId].tarId[len] = emptySpace;
        printf("Write links: ");
        char newName[32][32];
        for (int i=0;i< 32; i++)
        {
            scanf("%s", &newName[i]);
            if (!strcmp(newName[i], ":d"))
            {
                break;
            }
            int buffId = findIdByName(newName[i],'o');
            if (buffId == -1)
            {
                printf("not found");
                continue;
            }else{
                len = findLengthBeforeZero(notes[emptySpace].tarId);
                notes[emptySpace].tarId[len] = buffId;

                len = findLengthBeforeZero(notes[buffId].tarId);
                notes[buffId].tarId[len] = emptySpace;
            }
        }
        
        notesLen++;

        return;
    }

    if (!strcmp(command, "mv")){
        char name[32]; scanf("%s",&name);
        int id;
        if (strcmp(name, ".")){
            id = findIdByName(name, 'i');
        }else{
            id = currId;
        }
        if (id == -1){
            printf("%s\n", "not found in note");
            return;
        }

        scanf("%s", &notes[id].name);
    }
    
    

    if (!strcmp(command, "at")){ //add target note
        char name[32]; scanf("%s",&name);
        int id = findIdByName(name, 'o');
        if (id == -1){
            printf("%s\n", "not found");
            return;
        }
         
        int tarLen = findLengthBeforeZero(notes[currId].tarId);
        notes[currId].tarId[tarLen] = id;

        tarLen = findLengthBeforeZero(notes[id].tarId);
                notes[id].tarId[tarLen] = currId;
    }


    if (!strcmp(command, "exit")){
        exit(0);
    }

}






void saveToFile(const char *filename) {
    FILE *file = fopen(filename, "wb");
    if (!file) {
        perror("Failed to open file for saving");
        return;
    }

    // Save notesLen and currId
    fwrite(&notesLen, sizeof(notesLen), 1, file);
    fwrite(&currId, sizeof(currId), 1, file);

    // Save the notes array
    fwrite(notes, sizeof(Note), notesLen, file);

    fclose(file);
    //printf("Data saved successfully to %s\n", filename);
}
void loadFromFile(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        perror("Failed to open file for loading");
        return;
    }

    // Load notesLen and currId
    fread(&notesLen, sizeof(notesLen), 1, file);
    fread(&currId, sizeof(currId), 1, file);

    // Load the notes array
    fread(notes, sizeof(Note), notesLen, file);

    fclose(file);
    printf("Data loaded successfully from %s\n", filename);
}

int findIdByName(char name[], char tar){
    if (tar == 'i'){
        int len = findLengthBeforeZero(notes[currId].tarId);
        for (int i = 0; i < len; i++) {
            if (strcmp(notes[notes[currId].tarId[i]].name, name) == 0) {
                return notes[currId].tarId[i]; // Return the index of the note with the matching name   int currId
            }
        }
    }else{
        for (int i = 0; i < notesLen; i++) {
            if (strcmp(notes[i].name, name) == 0) {
                return i; // Return the index of the note with the matching name
            }
        }
    }
    return -1; // Return -1 if no matching note is found
}
int findLengthBeforeZeroNote(Note arr[]){
    int length = 1;
    for (int i = 1; i < 256; i++) {
        if (arr[i].name[0] == '\0' ) {
            
            break; // Stop counting when a 0 is encountered
             
        }
        length++;
    }
    return length;
}
int findLengthBeforeZero(int arr[]) {
    
    int length = 1;
    for (int i = 1; i < 256; i++) {
        if (arr[i] == 0) {
            break; // Stop counting when a 0 is encountered
        }
        length++;
    }
    return length;
}


int *removeRepeatingTargets(Note arr[], int id){ // ne bag a ficha
    int len = findLengthBeforeZero(arr[id].tarId);
    for (int i=0;i<len;i++){
        for (int j=i+1;j<len;j++){
            if (arr[id].tarId[i] == arr[id].tarId[j]){
                arr[id].tarId[j] = 0;
                

            }
        }
    }
    return arr[id].tarId;
}
