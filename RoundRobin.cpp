// #include <iostream>
// #include <queue>
// #include <vector>

// using namespace std;

// // Cấu trúc tiến trình
// struct Process {
//     int id;              // Mã tiến trình
//     int arrivalTime;      // Thời gian đến
//     int burstTime;        // Thời gian thực thi ban đầu
//     int remainingTime;    // Thời gian còn lại để hoàn thành
//     int startTime;        // Thời gian bắt đầu thực thi lần đầu
//     int finishTime;       // Thời gian hoàn thành
//     int waitTime;         // Thời gian chờ
//     int turnaroundTime;   // Thời gian quay vòng
// };

// // Hàm mô phỏng thuật toán Round Robin
// void roundRobinScheduling(vector<Process>& processes, int timeQuantum) {
//     queue<int> processQueue;  // Hàng đợi chứa chỉ số của các tiến trình
//     int currentTime = 0;      // Thời gian hiện tại của hệ thống
//     int completedProcesses = 0; // Số tiến trình đã hoàn thành
//     int n = processes.size(); // Số lượng tiến trình

//     // Đưa các tiến trình đến hệ thống vào hàng đợi
//     for (int i = 0; i < n; ++i) {
//         if (processes[i].arrivalTime <= currentTime) {
//             processQueue.push(i);  // Đưa chỉ số của tiến trình vào hàng đợi
//         }
//     }

//     // Vòng lặp xử lý các tiến trình theo Round Robin
//     while (completedProcesses < n) {
//         if (!processQueue.empty()) {
//             int i = processQueue.front(); // Lấy chỉ số tiến trình đầu tiên trong hàng đợi
//             processQueue.pop();            // Xóa tiến trình khỏi hàng đợi

//             // Nếu tiến trình chưa bắt đầu, cập nhật startTime
//             if (processes[i].remainingTime == processes[i].burstTime) {
//                 processes[i].startTime = currentTime;
//             }

//             // Nếu thời gian thực thi còn lại của tiến trình nhỏ hơn hoặc bằng time quantum
//             if (processes[i].remainingTime <= timeQuantum) {
//                 // Tiến trình hoàn thành trong khoảng time quantum này
//                 currentTime += processes[i].remainingTime;
//                 processes[i].remainingTime = 0;
//                 processes[i].finishTime = currentTime; // Cập nhật thời gian hoàn thành
//                 processes[i].turnaroundTime = processes[i].finishTime - processes[i].arrivalTime; // Thời gian quay vòng
//                 processes[i].waitTime = processes[i].turnaroundTime - processes[i].burstTime;     // Thời gian chờ

//                 cout << "Process " << processes[i].id << " finished at time " << currentTime << endl;
//                 completedProcesses++; // Tăng số tiến trình đã hoàn thành
//             }
//             else {
//                 // Nếu tiến trình không thể hoàn thành, xử lý trong time quantum và cập nhật thời gian còn lại
//                 currentTime += timeQuantum;
//                 processes[i].remainingTime -= timeQuantum;

//                 cout << "Process " << processes[i].id << " executed for " << timeQuantum << " units, remaining time: " << processes[i].remainingTime << endl;

//                 // Đưa tiến trình về cuối hàng đợi nếu nó chưa hoàn thành
//                 processQueue.push(i);
//             }

//             // Đưa các tiến trình mới đến vào hàng đợi
//             for (int j = 0; j < n; ++j) {
//                 if (processes[j].arrivalTime <= currentTime && processes[j].remainingTime > 0) {
//                     bool alreadyInQueue = false;
//                     queue<int> tempQueue = processQueue;

//                     // Kiểm tra nếu tiến trình đã có trong hàng đợi
//                     while (!tempQueue.empty()) {
//                         if (tempQueue.front() == j) {
//                             alreadyInQueue = true;
//                             break;
//                         }
//                         tempQueue.pop();
//                     }

//                     // Chỉ thêm vào hàng đợi nếu chưa có
//                     if (!alreadyInQueue) {
//                         processQueue.push(j);
//                     }
//                 }
//             }
//         }
//         else {
//             // Nếu hàng đợi trống, tăng thời gian hiện tại
//             currentTime++;
//         }
//     }
// }

// int main() {
//     int n; // Số lượng tiến trình
//     int timeQuantum; // Thời gian time quantum

//     cout << "Enter number of processes: ";
//     cin >> n;

//     vector<Process> processes(n); // Danh sách tiến trình

//     // Nhập dữ liệu cho từng tiến trình
//     for (int i = 0; i < n; ++i) {
//         cout << "Enter arrival time and burst time for process " << i + 1 << ": ";
//         cin >> processes[i].arrivalTime >> processes[i].burstTime;
//         processes[i].id = i + 1;
//         processes[i].remainingTime = processes[i].burstTime; // Thời gian còn lại ban đầu bằng burst time
//         processes[i].startTime = -1;   // Chưa bắt đầu
//         processes[i].finishTime = -1;  // Chưa hoàn thành
//     }

//     // Nhập giá trị time quantum
//     cout << "Enter time quantum: ";
//     cin >> timeQuantum;

//     // Gọi hàm thực hiện Round Robin
//     cout << "Round Robin Scheduling:" << endl;
//     roundRobinScheduling(processes, timeQuantum);

//     // Biến tính tổng thời gian chờ và thời gian quay vòng
//     double totalWaitTime = 0;
//     double totalTurnaroundTime = 0;

//     // In kết quả các tiến trình sau khi hoàn thành
//     cout << "\nProcess\tArrival\tBurst\tStart\tFinish\tWait\tTurnaround\n";
//     for (const auto& process : processes) {
//         cout << process.id << "\t" << process.arrivalTime << "\t" << process.burstTime
//             << "\t" << process.startTime << "\t" << process.finishTime
//             << "\t" << process.waitTime << "\t" << process.turnaroundTime << endl;

//         totalWaitTime += process.waitTime;
//         totalTurnaroundTime += process.turnaroundTime;
//     }

//     // Tính và in thời gian chờ trung bình và thời gian quay vòng trung bình
//     double averageWaitTime = totalWaitTime / n;
//     double averageTurnaroundTime = totalTurnaroundTime / n;

//     cout << "\nAverage waiting time: " << averageWaitTime << endl;
//     cout << "Average turnaround time: " << averageTurnaroundTime << endl;

//     return 0;
// }



//#include <climits>
//#include <iostream>
//using namespace std;
//
//struct Process
//{
//    int AT, BT, ST[20], WT, FT, TAT, pos;
//};
//
//int quant;
//
//int main()
//{
//    int n, i, j;
//
//    // Taking Input
//    cout << "Enter the no. of processes: ";
//    cin >> n;
//    Process* p = new Process[n]; // Sử dụng mảng động
//
//    cout << "Enter the quantum: " << endl;
//    cin >> quant;
//
//    cout << "Enter the process numbers: " << endl;
//    for (i = 0; i < n; i++)
//        cin >> p[i].pos;
//
//    cout << "Enter the Arrival time of processes: " << endl;
//    for (i = 0; i < n; i++)
//        cin >> p[i].AT;
//
//    cout << "Enter the Burst time of processes: " << endl;
//    for (i = 0; i < n; i++)
//        cin >> p[i].BT;
//
//    // Declaring variables
//    int c = n;
//    int** s = new int* [n]; // Sử dụng mảng động
//    for (i = 0; i < n; i++)
//        s[i] = new int[20];
//
//    float time = 0, mini = INT_MAX, * b = new float[n], * a = new float[n];
//
//    // Initializing burst and arrival time arrays
//    int index = -1;
//    for (i = 0; i < n; i++)
//    {
//        b[i] = p[i].BT;
//        a[i] = p[i].AT;
//        for (j = 0; j < 20; j++)
//        {
//            s[i][j] = -1;
//        }
//    }
//
//    int tot_wt, tot_tat;
//    tot_wt = 0;
//    tot_tat = 0;
//    bool flag = false;
//
//    while (c != 0)
//    {
//        mini = INT_MAX;
//        flag = false;
//
//        for (i = 0; i < n; i++)
//        {
//            float p = time + 0.1;
//            if (a[i] <= p && mini > a[i] && b[i] > 0)
//            {
//                index = i;
//                mini = a[i];
//                flag = true;
//            }
//        }
//
//        // if at =1 then loop gets out hence set flag to false
//        if (!flag)
//        {
//            time++;
//            continue;
//        }
//
//        // calculating start time
//        j = 0;
//
//        while (s[index][j] != -1)
//        {
//            j++;
//        }
//
//        if (s[index][j] == -1)
//        {
//            s[index][j] = time;
//            p[index].ST[j] = time;
//        }
//
//        if (b[index] <= quant)
//        {
//            time += b[index];
//            b[index] = 0;
//        }
//        else
//        {
//            time += quant;
//            b[index] -= quant;
//        }
//
//        if (b[index] > 0)
//        {
//            a[index] = time + 0.1;
//        }
//
//        // calculating arrival, burst, final times
//        if (b[index] == 0)
//        {
//            c--;
//            p[index].FT = time;
//            p[index].WT = p[index].FT - p[index].AT - p[index].BT;
//            tot_wt += p[index].WT;
//            p[index].TAT = p[index].BT + p[index].WT;
//            tot_tat += p[index].TAT;
//        }
//    } // end of while loop
//
//    // Printing output
//    cout << "Process number ";
//    cout << "Arrival time ";
//    cout << "Burst time ";
//    cout << "\tStart time";
//    j = 0;
//    while (j != 10)
//    {
//        j += 1;
//        cout << " ";
//    }
//    cout << "\t\tFinal time";
//    cout << "\tWait Time ";
//    cout << "\tTurnAround Time" << endl;
//
//    for (i = 0; i < n; i++)
//    {
//        cout << p[i].pos << "\t\t";
//        cout << p[i].AT << "\t\t";
//        cout << p[i].BT << "\t";
//        j = 0;
//        int v = 0;
//        while (s[i][j] != -1)
//        {
//            cout << p[i].ST[j] << " ";
//            j++;
//            v += 3;
//        }
//        while (v != 40)
//        {
//            cout << " ";
//            v += 1;
//        }
//        cout << p[i].FT << "\t\t";
//        cout << p[i].WT << "\t\t";
//        cout << p[i].TAT << endl;
//    }
//
//    // Calculating average wait time and turnaround time
//    double avg_wt, avg_tat;
//    avg_wt = tot_wt / static_cast<double>(n);
//    avg_tat = tot_tat / static_cast<double>(n);
//
//    // Printing average wait time and turnaround time
//    cout << "The average wait time is: " << avg_wt << endl;
//    cout << "The average TurnAround time is: " << avg_tat << endl;
//
//    // Giải phóng bộ nhớ động
//    delete[] p;
//    delete[] b;
//    delete[] a;
//    for (i = 0; i < n; i++)
//        delete[] s[i];
//    delete[] s;
//
//    return 0;
//}

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

struct Process {
    int pid; // Process ID
    int bt;  // Burst Time
    int at;  // Arrival Time
};

bool compareArrival(Process a, Process b) {
    return a.at < b.at;
}

void findWaitingTime(vector<Process> &proc, vector<int> &wt, vector<int> &completion_time, int quantum) {
    int n = proc.size();
    vector<int> rem_bt(n);  // Remaining burst time
    vector<int> start_time(n, -1); // Thời điểm tiến trình bắt đầu chạy lần đầu tiên
    for (int i = 0; i < n; i++)
        rem_bt[i] = proc[i].bt;

    int t = 0; // Thời gian hiện tại
    queue<int> q;
    vector<bool> inQueue(n, false);

    // Bắt đầu với tiến trình đầu tiên (giả sử các tiến trình được sắp xếp theo thời gian đến)
    q.push(0);
    inQueue[0] = true;

    while (!q.empty()) {
        int i = q.front();
        q.pop();

        // Ghi lại thời gian bắt đầu chạy lần đầu của tiến trình
        if (start_time[i] == -1) {
            start_time[i] = t;
        }

        // Nếu burst time lớn hơn quantum, tiến trình cần quay lại
        if (rem_bt[i] > quantum) {
            t += quantum;
            rem_bt[i] -= quantum;
        } else { // Tiến trình hoàn thành
            t += rem_bt[i];
            rem_bt[i] = 0;
            completion_time[i] = t;
            wt[i] = t - proc[i].bt - proc[i].at; // Tính thời gian chờ
        }

        // Kiểm tra và thêm các tiến trình mới vào hàng đợi
        for (int j = 0; j < n; j++) {
            if (proc[j].at <= t && rem_bt[j] > 0 && !inQueue[j]) {
                q.push(j);
                inQueue[j] = true;
            }
        }

        // Nếu tiến trình chưa hoàn thành, đưa nó quay lại hàng đợi
        if (rem_bt[i] > 0)
            q.push(i);
    }
}

void findTurnAroundTime(vector<Process> &proc, vector<int> &wt, vector<int> &tat) {
    int n = proc.size();
    for (int i = 0; i < n; i++)
        tat[i] = proc[i].bt + wt[i];  // Thời gian quay vòng = burst time + thời gian chờ
}

void findAvgTime(vector<Process> &proc, int quantum) {
    int n = proc.size();
    vector<int> wt(n), tat(n), completion_time(n);

    findWaitingTime(proc, wt, completion_time, quantum);
    findTurnAroundTime(proc, wt, tat);

    int total_wt = 0, total_tat = 0;
    cout << "Process\tArrival\tBurst\tCompletion\tWaiting\tTurnaround\n";
    for (int i = 0; i < n; i++) {
        total_wt += wt[i];
        total_tat += tat[i];
        cout << "P" << proc[i].pid << "\t" << proc[i].at << "\t" << proc[i].bt << "\t"
             << completion_time[i] << "\t\t" << wt[i] << "\t" << tat[i] << endl;
    }

    cout << "\nThời gian chờ trung bình = " << (float)total_wt / n << endl;
    cout << "Thời gian hoàn thành trung bình = " << (float)total_tat / n << endl;
}

int main() {
    int n, quantum;
    cout << "Nhập số lượng tiến trinh: ";
    cin >> n;
    vector<Process> proc(n);
    cout << "Nhập thời gian burst và thời gian đến của các tiến trình:\n";
    for (int i = 0; i < n; i++) {
        cout << "P" << i + 1 << ":\n";
        cout << "Burst Time: ";
        cin >> proc[i].bt;
        cout << "Arrival Time: ";
        cin >> proc[i].at;
        proc[i].pid = i + 1;
    }
    cout << "Nhập thời gian quantum: ";
    cin >> quantum;

    // Sắp xếp các tiến trình theo thời gian đến
    sort(proc.begin(), proc.end(), compareArrival);

    findAvgTime(proc, quantum);
    return 0;
}
