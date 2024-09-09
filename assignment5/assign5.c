#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string> // Include this for std::string
using namespace std;

int allocated[5][3] = {{0,1,0},{2,0,0},{3,0,2},{2,1,1},{0,0,2}};
int maxNeed[5][3] = {{7,5,3},{3,2,2},{9,0,2},{4,2,2},{5,3,3}};

vector<vector<int>> remaining;
vector<int> available;
vector<string> path;
vector<bool> isDone(5, false); // Initialize isDone with false values
int count = 0;
int n = 5;
int total[3] = {10,5,7};

void calRemaining() {
    int i;
    for (i = 0; i < n; i++) {
        vector<int> temp;
        temp.push_back(maxNeed[i][0] - allocated[i][0]);
        temp.push_back(maxNeed[i][1] - allocated[i][1]);
        temp.push_back(maxNeed[i][2] - allocated[i][2]);
        remaining.push_back(temp);
    }
}

void calAvailable() {
    int a = 0, b = 0, c = 0;
    for (int i = 0; i < n; i++) {
        a += allocated[i][0];
        b += allocated[i][1];
        c += allocated[i][2];
    }
    available.push_back(total[0] - a); // Compute the remaining resources
    available.push_back(total[1] - b);
    available.push_back(total[2] - c);
}

void findPath() {
    int pointer = 0;
    while (count < n) {
        if (remaining[pointer][0] <= available[0] && remaining[pointer][1] <= available[1] &&
            remaining[pointer][2] <= available[2] && !isDone[pointer]) {
            count++;
            available[0] += allocated[pointer][0];
            available[1] += allocated[pointer][1];
            available[2] += allocated[pointer][2];
            isDone[pointer] = true;
            path.push_back("P" + to_string(pointer + 1));
        }
        pointer = (pointer + 1) % n; // Move to the next process
    }
}

int main() {
    calRemaining();
    calAvailable();
    findPath();
    int i, j;
    for (i = 0; i < n; i++) {
        for (j = 0; j < 3; j++) {
        printf("%d ", remaining[i][j]);
    }
    printf("\n");
    }

    printf("\nAvailable are: ");
    for (i = 0; i < 3; i++) {
        printf("%d ", available[i]);
    }
    
    printf("\n");
    printf("The Path Sequence is: ");

    for (i = 0; i < path.size()-1; i++) {
        printf("%s -> ", path[i].c_str());
    }

    printf("%s",path[path.size()-1].c_str());
    printf("\n");
    return 0;
}