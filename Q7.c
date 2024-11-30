#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char contentTitle[100];
    float averageRating;
    int contentLength;
    char encodingFormat[50];
} ContentDetails;

typedef struct {
    double *categoryEngagementScores;
} UserEngagement;

typedef struct {
    int *preferredResolution;
    double *viewingHistory;
    double *dataConsumption;
} UserDevicePreferences;

double **userEngagementMatrix;
UserDevicePreferences **userDevicesMatrix;
ContentDetails ***contentDataMatrix;

void initializeUserEngagement(int numUsers, int numCategories);
void initializeDevicePreferences(int numUsers, int numDevices);
void initializeContentDetails(int numCategories, int numContents);
void updateUserEngagementScore(int userIndex, int categoryIndex, double score);
void updateDevicePreference(int userIndex, int deviceIndex, int resolution, double viewingHistory, double dataUsage);
void displayContentDetails(int categoryIndex, int contentIndex);
void freeAllocatedMemory(int numUsers, int numCategories, int numDevices, int numContents);

int main() {
    int totalUsers = 4;
    int totalCategories = 3;
    int totalDevices = 2;
    int totalContents = 5;

    initializeUserEngagement(totalUsers, totalCategories);
    initializeDevicePreferences(totalUsers, totalDevices);
    initializeContentDetails(totalCategories, totalContents);

    updateUserEngagementScore(0, 1, 0.75);
    updateUserEngagementScore(1, 0, 0.85);

    updateDevicePreference(0, 0, 1080, 120.5, 700.0);
    updateDevicePreference(2, 1, 720, 95.0, 400.0);

    displayContentDetails(1, 2);

    freeAllocatedMemory(totalUsers, totalCategories, totalDevices, totalContents);

    return 0;
}

void initializeUserEngagement(int numUsers, int numCategories) {
    userEngagementMatrix = (double **)malloc(numUsers * sizeof(double *));
    for (int i = 0; i < numUsers; i++) {
        userEngagementMatrix[i] = (double *)malloc(numCategories * sizeof(double));
        for (int j = 0; j < numCategories; j++) {
            userEngagementMatrix[i][j] = 0.0;
        }
    }
}

void initializeDevicePreferences(int numUsers, int numDevices) {
    userDevicesMatrix = (UserDevicePreferences **)malloc(numUsers * sizeof(UserDevicePreferences *));
    for (int i = 0; i < numUsers; i++) {
        userDevicesMatrix[i] = (UserDevicePreferences *)malloc(numDevices * sizeof(UserDevicePreferences));
        for (int j = 0; j < numDevices; j++) {
            userDevicesMatrix[i][j].preferredResolution = (int *)malloc(1 * sizeof(int));
            userDevicesMatrix[i][j].viewingHistory = (double *)malloc(1 * sizeof(double));
            userDevicesMatrix[i][j].dataConsumption = (double *)malloc(1 * sizeof(double));

            userDevicesMatrix[i][j].preferredResolution[0] = 1080;
            userDevicesMatrix[i][j].viewingHistory[0] = 0.0;
            userDevicesMatrix[i][j].dataConsumption[0] = 0.0;
        }
    }
}

void initializeContentDetails(int numCategories, int numContents) {
    contentDataMatrix = (ContentDetails ***)malloc(numCategories * sizeof(ContentDetails **));
    for (int i = 0; i < numCategories; i++) {
        contentDataMatrix[i] = (ContentDetails **)malloc(numContents * sizeof(ContentDetails *));
        for (int j = 0; j < numContents; j++) {
            contentDataMatrix[i][j] = (ContentDetails *)malloc(sizeof(ContentDetails));
            
            if (i == 0)  
                sprintf(contentDataMatrix[i][j]->contentTitle, "Action Movie %d", j + 1);
            else if (i == 1)  
                sprintf(contentDataMatrix[i][j]->contentTitle, "Drama Movie %d", j + 1);
            else  
                sprintf(contentDataMatrix[i][j]->contentTitle, "Comedy Movie %d", j + 1);

            contentDataMatrix[i][j]->averageRating = (i == 0) ? 8.0 : (i == 1) ? 7.5 : 6.5;
            contentDataMatrix[i][j]->contentLength = (i == 0) ? 110 : 120;  
            strcpy(contentDataMatrix[i][j]->encodingFormat, "H.264");
        }
    }
}

void updateUserEngagementScore(int userIndex, int categoryIndex, double score) {
    userEngagementMatrix[userIndex][categoryIndex] = score;
}

void updateDevicePreference(int userIndex, int deviceIndex, int resolution, double viewingTime, double dataUsage) {
    userDevicesMatrix[userIndex][deviceIndex].preferredResolution[0] = resolution;
    userDevicesMatrix[userIndex][deviceIndex].viewingHistory[0] = viewingTime;
    userDevicesMatrix[userIndex][deviceIndex].dataConsumption[0] = dataUsage;
}

void displayContentDetails(int categoryIndex, int contentIndex) {
    ContentDetails *content = contentDataMatrix[categoryIndex][contentIndex];
    printf("Content Title: %s\n", content->contentTitle);
    printf("Average Rating: %.1f\n", content->averageRating);
    printf("Content Length: %d minutes\n", content->contentLength);
    printf("Encoding Format: %s\n", content->encodingFormat);
}

void freeAllocatedMemory(int numUsers, int numCategories, int numDevices, int numContents) {
    for (int i = 0; i < numUsers; i++) {
        free(userEngagementMatrix[i]);
    }
    free(userEngagementMatrix);

    for (int i = 0; i < numUsers; i++) {
        for (int j = 0; j < numDevices; j++) {
            free(userDevicesMatrix[i][j].preferredResolution);
            free(userDevicesMatrix[i][j].viewingHistory);
            free(userDevicesMatrix[i][j].dataConsumption);
        }
        free(userDevicesMatrix[i]);
    }
    free(userDevicesMatrix);

    for (int i = 0; i < numCategories; i++) {
        for (int j = 0; j < numContents; j++) {
            free(contentDataMatrix[i][j]);
        }
        free(contentDataMatrix[i]);
    }
    free(contentDataMatrix);
}
