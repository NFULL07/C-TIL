#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct student {
    char name[20];
    char gender[5];
    char city[20];
    char dept[20];
    float score;
    int height;
    int weight;
};

struct student* arr;
int count = 0;

int count_lines(char* filename) {
    FILE* fp = fopen(filename, "r");
    int lines = 0;
    char dummy[200];
    while (fgets(dummy, 200, fp) != NULL)
        lines++;
    fclose(fp);
    return lines;
}

void process_create() {
    arr = (struct student*)malloc(sizeof(struct student) * 100);
}

void process_load(char* filename) {
    FILE* fp = fopen(filename, "r");
    if (fp == NULL) {
        perror("Failed to open the file.");
        exit(0);
    }
    while (!feof(fp)) {
        fscanf(fp, "%s %s %s %s %f %d %d",
            arr[count].name,
            arr[count].gender,
            arr[count].city,
            arr[count].dept,
            &arr[count].score,
            &arr[count].height,
            &arr[count].weight);
        count++;
    }
    fclose(fp);

    struct student tmp;
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - 1 - i; j++) {
            if (strcmp(arr[j].name, arr[j + 1].name) > 0) {
                tmp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = tmp;
            }
        }
    }
}

void process_print() {
    for (int i = 0; i < count; i++) {
        printf("%s %s %s %s %.2f %d %d\n",
            arr[i].name,
            arr[i].gender,
            arr[i].city,
            arr[i].dept,
            arr[i].score,
            arr[i].height,
            arr[i].weight);
    }
}

void process_insert(char* name, char* gender, char* city,
    char* dept, char* score, char* height, char* weight) {
    int i;
    for (i = 0; i < count; i++) {
        if (strcmp(arr[i].name, name) > 0)
            break;
    }
    for (int j = count - 1; j >= i; j--)
        arr[j + 1] = arr[j];
    strcpy(arr[i].name, name);
    strcpy(arr[i].gender, gender);
    strcpy(arr[i].city, city);
    strcpy(arr[i].dept, dept);
    arr[i].score = atof(score);
    arr[i].height = atoi(height);
    arr[i].weight = atoi(weight);
    count++;
}

void process_delete(char* name) {
    int i;
    int found = -1;
    for (i = 0; i < count; i++) {
        if (strcmp(arr[i].name, name) == 0) {
            found = i;
            break;
        }
    }
    if (found == -1) {
        printf("%s is not found.\n", name);
        return;
    }
    for (int j = found; j < count - 1; j++)
        arr[j] = arr[j + 1];
    count--;
}

void process_search(char* name) {
    for (int i = 0; i < count; i++) {
        if (strcmp(arr[i].name, name) == 0) {
            printf("%s %s %s %s %.2f %d %d\n",
                arr[i].name,
                arr[i].gender,
                arr[i].city,
                arr[i].dept,
                arr[i].score,
                arr[i].height,
                arr[i].weight);
            return;
        }
    }
    printf("%s is not found.\n", name);
}

void main() {
    int nlines = count_lines("input.txt");
    FILE* fp = fopen("input.txt", "r");

    char tok1[32], tok2[32], tok3[32], tok4[32];
    char tok5[32], tok6[32], tok7[32], tok8[32];

    for (int i = 0; i < nlines; i++) {
        fscanf(fp, "%s", tok1);
        if (strcmp(tok1, "CREATE") == 0) {
            process_create();
        }
        else if (strcmp(tok1, "LOAD") == 0) {
            fscanf(fp, "%s", tok2);
            process_load(tok2);
        }
        else if (strcmp(tok1, "PRINT") == 0) {
            process_print();
        }
        else if (strcmp(tok1, "INSERT") == 0) {
            fscanf(fp, "%s %s %s %s %s", tok2, tok3, tok4, tok5, tok6);
            fscanf(fp, "%s %s", tok7, tok8);
            process_insert(tok2, tok3, tok4, tok5, tok6, tok7, tok8);
        }
        else if (strcmp(tok1, "DELETE") == 0) {
            fscanf(fp, "%s", tok2);
            process_delete(tok2);
        }
        else if (strcmp(tok1, "SEARCH") == 0) {
            fscanf(fp, "%s", tok2);
            process_search(tok2);
        }
        else {
            printf("%s is not a keyword.\n", tok1);
        }
        printf("%s done ===============\n\n", tok1);
    }
    fclose(fp);
}