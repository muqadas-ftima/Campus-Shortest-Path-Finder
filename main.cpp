#include <iostream>
#include <vector>
#include <string>
#include <climits>
using namespace std;

const int N = 6;

string locations[N] = {
    "Main Gate",
    "Library",
    "Computer Lab",
    "Cafeteria",
    "Science Block",
    "Admin Block"
};

int graph[N][N] = {
    {0, 4, 2, 0, 0, 0},
    {4, 0, 1, 5, 0, 0},
    {2, 1, 0, 8, 10, 0},
    {0, 5, 8, 0, 2, 6},
    {0, 0, 10, 2, 0, 3},
    {0, 0, 0, 6, 3, 0}
};

void showLocations() {
    cout << "\n===== CAMPUS LOCATIONS =====\n";

    for (int i = 0; i < N; i++) {
        cout << i + 1 << ". " << locations[i] << endl;
    }
}

void shortestPath(int source, int destination) {
    int distance[N];
    bool visited[N] = {false};
    int parent[N];

    for (int i = 0; i < N; i++) {
        distance[i] = INT_MAX;
        parent[i] = -1;
    }

    distance[source] = 0;

    for (int count = 0; count < N - 1; count++) {
        int minimum = INT_MAX;
        int current = -1;

        for (int i = 0; i < N; i++) {
            if (!visited[i] && distance[i] < minimum) {
                minimum = distance[i];
                current = i;
            }
        }

        if (current == -1)
            break;

        visited[current] = true;

        for (int i = 0; i < N; i++) {
            if (graph[current][i] > 0 &&
                !visited[i] &&
                distance[current] + graph[current][i] < distance[i]) {

                distance[i] = distance[current] + graph[current][i];
                parent[i] = current;
            }
        }
    }

    if (distance[destination] == INT_MAX) {
        cout << "\nNo route available.\n";
        return;
    }

    int path[N];
    int size = 0;
    int current = destination;

    while (current != -1) {
        path[size++] = current;
        current = parent[current];
    }

    cout << "\n===== SHORTEST ROUTE =====\n";

    for (int i = size - 1; i >= 0; i--) {
        cout << locations[path[i]];

        if (i > 0)
            cout << " -> ";
    }

    cout << "\nTotal Distance: "
         << distance[destination] << " units\n";
}

int main() {
    int choice;
    int source, destination;

    do {
        cout << "\n===== CAMPUS PATH FINDER =====\n";
        cout << "1. Show Campus Locations\n";
        cout << "2. Find Shortest Route\n";
        cout << "0. Exit\n";

        cout << "Enter Choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                showLocations();
                break;

            case 2:
                showLocations();

                cout << "\nEnter Starting Location (1-6): ";
                cin >> source;

                cout << "Enter Destination (1-6): ";
                cin >> destination;

                if (source < 1 || source > N ||
                    destination < 1 || destination > N) {
                    cout << "Invalid location number.\n";
                }
                else if (source == destination) {
                    cout << "You are already at this location.\n";
                }
                else {
                    shortestPath(source - 1, destination - 1);
                }
                break;

            case 0:
                cout << "Program closed.\n";
                break;

            default:
                cout << "Invalid choice.\n";
        }

    } while (choice != 0);

    return 0;
}

