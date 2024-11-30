#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SUPPLIES 100
#define MAX_NAME_LEN 50

typedef struct {
    char** supplies;
    int supplyCount;
} Species;

void initializeInventory(Species** speciesSupplies, int speciesCount) {
    *speciesSupplies = (Species*)malloc(speciesCount * sizeof(Species));
    for (int i = 0; i < speciesCount; i++) {
        (*speciesSupplies)[i].supplies = NULL;
        (*speciesSupplies)[i].supplyCount = 0;
    }
}

void addSupplies(Species* species) {
    int supplyCount;
    printf("Enter the number of supplies: ");
    scanf("%d", &supplyCount);
    species->supplies = (char**)malloc(supplyCount * sizeof(char*));
    species->supplyCount = supplyCount;
    for (int i = 0; i < supplyCount; i++) {
        species->supplies[i] = (char*)malloc(MAX_NAME_LEN * sizeof(char));
        printf("Enter supply name for item %d: ", i + 1);
        scanf("%s", species->supplies[i]);
    }
}

void updateSupply(Species* species, int index, const char* newName) {
    if (index >= 0 && index < species->supplyCount) {
        strcpy(species->supplies[index], newName);
    } else {
        printf("Invalid index.\n");
    }
}

void removeSpecies(Species* speciesSupplies, int index, int* speciesCount) {
    if (index >= 0 && index < *speciesCount) {
        for (int i = 0; i < speciesSupplies[index].supplyCount; i++) {
            free(speciesSupplies[index].supplies[i]);
        }
        free(speciesSupplies[index].supplies);
        for (int i = index; i < *speciesCount - 1; i++) {
            speciesSupplies[i] = speciesSupplies[i + 1];
        }
        (*speciesCount)--;
        speciesSupplies = (Species*)realloc(speciesSupplies, (*speciesCount) * sizeof(Species));
    } else {
        printf("Invalid index.\n");
    }
}

void displayInventory(Species* speciesSupplies, int speciesCount) {
    for (int i = 0; i < speciesCount; i++) {
        printf("Species %d:\n", i + 1);
        for (int j = 0; j < speciesSupplies[i].supplyCount; j++) {
            printf("  Supply %d: %s\n", j + 1, speciesSupplies[i].supplies[j]);
        }
    }
}

int main() {
    int speciesCount, choice, speciesIndex, supplyIndex;
    char newSupplyName[MAX_NAME_LEN];
    Species* speciesSupplies;

    printf("Enter the number of species: ");
    scanf("%d", &speciesCount);
    initializeInventory(&speciesSupplies, speciesCount);

    while (1) {
        printf("\nMenu:\n");
        printf("1. Add supplies\n");
        printf("2. Update supply\n");
        printf("3. Remove species\n");
        printf("4. Display inventory\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter species index: ");
                scanf("%d", &speciesIndex);
                if (speciesIndex >= 1 && speciesIndex <= speciesCount) {
                    addSupplies(&speciesSupplies[speciesIndex - 1]);
                } else {
                    printf("Invalid species index.\n");
                }
                break;
            case 2:
                printf("Enter species index: ");
                scanf("%d", &speciesIndex);
                if (speciesIndex >= 1 && speciesIndex <= speciesCount) {
                    printf("Enter supply index: ");
                    scanf("%d", &supplyIndex);
                    printf("Enter new supply name: ");
                    scanf("%s", newSupplyName);
                    updateSupply(&speciesSupplies[speciesIndex - 1], supplyIndex - 1, newSupplyName);
                } else {
                    printf("Invalid species index.\n");
                }
                break;
            case 3:
                printf("Enter species index: ");
                scanf("%d", &speciesIndex);
                removeSpecies(speciesSupplies, speciesIndex - 1, &speciesCount);
                break;
            case 4:
                displayInventory(speciesSupplies, speciesCount);
                break;
            case 5:
                for (int i = 0; i < speciesCount; i++) {
                    for (int j = 0; j < speciesSupplies[i].supplyCount; j++) {
                        free(speciesSupplies[i].supplies[j]);
                    }
                    free(speciesSupplies[i].supplies);
                }
                free(speciesSupplies);
                return 0;
            default:
                printf("Invalid choice.\n");
        }
    }
}
