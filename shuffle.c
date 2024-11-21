#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *people[64];
char *assigned[64];


void shuffle(char *array[], size_t n) {
    int valid;
    do{
        valid = 1;
        for(size_t i = n - 1; i > 0; i--) {
            size_t j = rand() % (i + 1);
            char *temp = array[i];
            array[i] = array[j];
            array[j] = temp;
        }

        for(size_t i = 0; i < n; i++){
            if(strcmp(people[i], assigned[i]) == 0){
                valid = 0;
                break;
            }
        }
    } while(!valid);
}


int main(){
    size_t line_capacity = 0;
    char *line = NULL;

    FILE *file = fopen("peepool.txt", "r");
    if(file == NULL){
        perror("Couldn't open the file!");
        return 1;
    }

    int i = 0;
    while(getline(&line, &line_capacity, file) != -1){
        line[strcspn(line, "\n")] = '\0';

        if (i >= 64) {
            fprintf(stderr, "Too many entries in the file!\n");
            free(line);
            fclose(file);
            return 1;
        }

        people[i] = strdup(line);
        if (people[i] == NULL){
            perror("Failed to allocate memory for people");
            free(line);
            fclose(file);
            return 1;
        }
        assigned[i] = strdup(line);
        if (assigned[i] == NULL){
            perror("Failed to allocate memory for assigned");
            free(line);
            fclose(file);
            return 1;
        }
        i++;
    }

    free(line);
    fclose(file);

    shuffle(assigned, i);

    file = fopen("assigned.txt", "w");
    if(file == NULL){
        perror("Couldn't open the file!");
        return 1;
    }

    for (int j = 0; j < i; j++) {
        fprintf(file, "%s => %s\n", people[j], assigned[j]);
        free(people[j]);
        free(assigned[j]);
    }

    fclose(file);

    return 0;
}
