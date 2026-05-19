#include <iostream>
#include <queue>
using namespace std;

void printQueue(queue<int> q) {
    cout << "Queue: ";
    if (q.empty()) {
        cout << "Empty";
    } else {
        while (!q.empty()) {
            cout << "P" << q.front() << " ";
            q.pop();
        }
    }
    cout << endl;
}

int main() {
    int n, tq;
    cout << "Enter number of processes: ";
    cin >> n;
    int at[n], bt[n], rt[n], ct[n], tat[n], wt[n], res[n];
    bool inQueue[n] = {false};
    cout << "Enter Arrival Time and Burst Time:\n";
    for (int i = 0; i < n; i++) {
        cout << "P" << i+1 << " AT BT: ";
        cin >> at[i] >> bt[i];
        rt[i] = bt[i];
        res[i] = -1; 
    }
    cout << "Enter Time Quantum: ";
    cin >> tq;

    queue<int> q;
    int time = 0, completed = 0;
    for (int i = 0; i < n; i++) {
        if (at[i] == 0) {
            q.push(i);
            inQueue[i] = true;
        }
    }

    while (completed < n) {
        if (q.empty()) {
            time++;
            for (int i = 0; i < n; i++) {
                if (at[i] <= time && !inQueue[i] && rt[i] > 0) {
                    q.push(i);
                    inQueue[i] = true;
                }
            }
            continue;
        }

        int i = q.front();
        q.pop();
        if (res[i] == -1){
            res[i] = time - at[i];
        }

        if (rt[i] > tq) {
            time += tq;
            rt[i] -= tq;
        } else {
            time += rt[i];
            rt[i] = 0;
            ct[i] = time;
            completed++;
        }

        for (int j = 0; j < n; j++) {
            if (at[j] <= time && !inQueue[j] && rt[j] > 0) {
                q.push(j);
                inQueue[j] = true;
            }
        }
        if (rt[i] > 0)
            q.push(i);
    }

    for (int i = 0; i < n; i++) {
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];
    }

    cout << "\nP\tAT\tBT\tCT\tTAT\tWT\tRT\n";
    for (int i = 0; i < n; i++) {
        cout << "P" << i+1 << "\t"
             << at[i] << "\t"
             << bt[i] << "\t"
             << ct[i] << "\t"
             << tat[i] << "\t"
             << wt[i] << "\t"
             << res[i] << endl;
    }

    return 0;
}

