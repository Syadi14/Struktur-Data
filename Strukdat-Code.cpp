#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <ctime>
#include <algorithm>
#include <chrono>

using namespace std;

struct Log {
    int id;
    string timestamp;
    string level;
    string module;
    string message;
};

//fungsi untuk menyimpan log ke file
void saveLogs(const vector<Log>& logs) {

    ofstream file("logs.txt");

    for (const auto& log : logs) {

        file << log.id << ","
             << log.timestamp << ","
             << log.level << ","
             << log.module << ","
             << log.message << endl;
    }

    file.close();
}

void loadLogs(vector<Log>& logs) {

    ifstream file("logs.txt");
    string line;

    while (getline(file, line)) {

        stringstream ss(line);
        Log log;
        string temp;

        getline(ss, temp, ',');
        log.id = stoi(temp);

        getline(ss, log.timestamp, ',');
        getline(ss, log.level, ',');
        getline(ss, log.module, ',');
        getline(ss, log.message);

        logs.push_back(log);
    }

    file.close();
}

string toUpperCase(string text) {
    transform(text.begin(), text.end(), text.begin(), ::toupper);
    return text;
}

string getCurrentTimestamp() {
    time_t now = time(0);
    tm *ltm = localtime(&now);

    char buffer[20];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", ltm);

    return string(buffer);
}

//Menyimpan log ke vector
void insertLog(vector<Log>& logs) {

    Log newLog;

    cout << "ID Log: ";
    cin >> newLog.id;
    cin.ignore();

    newLog.timestamp = getCurrentTimestamp();

    cout << "Level (INFO/WARNING/ERROR): ";
    getline(cin, newLog.level);
    newLog.level = toUpperCase(newLog.level);

    cout << "Module: ";
    getline(cin, newLog.module);

    cout << "Message: ";
    getline(cin, newLog.message);

    // mulai timer
    auto start = chrono::high_resolution_clock::now();

    logs.push_back(newLog);

    // stop timer
    auto stop = chrono::high_resolution_clock::now();

    auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);

    cout << "Log berhasil ditambahkan.\n";
    cout << "Insert time: " << duration.count() << " microseconds\n";
}

//menampilkan semua log
void showLogs(const vector<Log>& logs) {
    for (const auto& log : logs) {
        cout << "ID: " << log.id << endl;
        cout << "Time: " << log.timestamp << endl;
        cout << "Level: " << log.level << endl;
        cout << "Module: " << log.module << endl;
        cout << "Message: " << log.message << endl;
        cout << "----------------------\n";
    }
}

//search log berdasarkan level
void searchByLevel(const vector<Log>& logs) {
    string level;

    cout << "Masukkan level log (INFO/WARNING/ERROR): ";
    cin >> level;

    for (const auto& log : logs) {
        if (log.level == level) {
            cout << log.id << " | "
                 << log.timestamp << " | "
                 << log.module << " | "
                 << log.message << endl;
        }
    }
}

//menampilkan log error
void showErrorLogs(const vector<Log>& logs) {
    for (const auto& log : logs) {
        if (log.level == "ERROR") {
            cout << log.id << " | "
                 << log.timestamp << " | "
                 << log.module << " | "
                 << log.message << endl;
        }
    }
}

//statistik log
void logStatistics(const vector<Log>& logs) {
    int info = 0;
    int warning = 0;
    int error = 0;

    for (const auto& log : logs) {
        if (log.level == "INFO") info++;
        else if (log.level == "WARNING") warning++;
        else if (log.level == "ERROR") error++;
    }

    cout << "INFO: " << info << endl;
    cout << "WARNING: " << warning << endl;
    cout << "ERROR: " << error << endl;
}

//simpan log ke file
void saveToFile(const vector<Log>& logs) {
    ofstream file("logs.txt");

    for (const auto& log : logs) {
        file << log.id << ","
             << log.timestamp << ","
             << log.level << ","
             << log.module << ","
             << log.message << endl;
    }

    file.close();
}

//load log dari file
void loadFromFile(vector<Log>& logs) {
    ifstream file("logs.txt");
    string line;

    while (getline(file, line)) {
        stringstream ss(line);
        Log log;
        string temp;

        getline(ss, temp, ',');
        log.id = stoi(temp);

        getline(ss, log.timestamp, ',');
        getline(ss, log.level, ',');
        getline(ss, log.module, ',');
        getline(ss, log.message);

        logs.push_back(log);
    }

    file.close();
}

//search log (waktu)
void searchByTime(const vector<Log>& logs) {

    string time;

    cout << "Masukkan waktu / tanggal (contoh: 2026-03-11): ";
    cin.ignore();
    getline(cin, time);

    bool found = false;

    for (const auto& log : logs) {

        if (log.timestamp.find(time) != string::npos) {

            cout << log.id << " | "
                 << log.timestamp << " | "
                 << log.level << " | "
                 << log.module << " | "
                 << log.message << endl;

            found = true;
        }
    }

    if (!found) {
        cout << "Log tidak ditemukan.\n";
    }
}

//search log (module)
void searchByModule(const vector<Log>& logs) {

    string module;

    cout << "Masukkan nama module: ";
    cin.ignore();
    getline(cin, module);

    bool found = false;

    for (const auto& log : logs) {

        if (log.module == module) {

            cout << log.id << " | "
                 << log.timestamp << " | "
                 << log.level << " | "
                 << log.module << " | "
                 << log.message << endl;

            found = true;
        }
    }

    if (!found) {
        cout << "Log tidak ditemukan.\n";
    }
}

//delete log (id)
void deleteLogByID(vector<Log>& logs) {

    int id;
    cout << "Masukkan ID log yang ingin dihapus: ";
    cin >> id;

    bool found = false;

    for (auto it = logs.begin(); it != logs.end(); it++) {

        if (it->id == id) {

            logs.erase(it);

            cout << "Log berhasil dihapus.\n";

            found = true;
            break;
        }
    }

    if (!found) {
        cout << "Log dengan ID tersebut tidak ditemukan.\n";
    }
}

//delete log lama (waktu)
void deleteOldLogs(vector<Log>& logs) {

    string timeLimit;

    cout << "Hapus log sebelum waktu (YYYY-MM-DD): ";
    cin.ignore();
    getline(cin, timeLimit);

    int before = logs.size();

    logs.erase(
        remove_if(logs.begin(), logs.end(),
        [&](Log log) {
            return log.timestamp < timeLimit;
        }),
        logs.end()
    );

    int after = logs.size();

    cout << before - after << " log berhasil dihapus.\n";
}

//menu program
int main() {

    vector<Log> logs;

    loadLogs(logs);

    int choice;

    do {

        cout << "\n===== LOG MONITORING SYSTEM =====\n";
        cout << "1 Insert Log\n";
        cout << "2 Show All Logs\n";
        cout << "3 Search by Level\n";
        cout << "4 Search by Time\n";
        cout << "5 Search by Module\n";
        cout << "6 Show Error Logs\n";
        cout << "7 Delete Log by Time\n";
        cout << "8 Delete Log by ID\n";
        cout << "9 Log Statistics\n";
        cout << "10 Save Logs\n";
        cout << "11 Exit\n";

        cout << "Choose: ";
        cin >> choice;

        switch (choice) {

    case 1:
        insertLog(logs);
        break;

    case 2:
        showLogs(logs);
        break;

    case 3:
        searchByLevel(logs);
        break;

    case 4:
        searchByTime(logs);
        break;

    case 5:
        searchByModule(logs);
        break;

    case 6:
        showErrorLogs(logs);
        break;

    case 7:
        deleteOldLogs(logs);
        break;

    case 8:
        deleteLogByID(logs);
        break;

    case 9:
        logStatistics(logs);
        break;

    case 10:
        saveLogs(logs);
        cout << "Log saved.\n";
        break;
}

    } while (choice != 11);

    saveLogs(logs);

    return 0;
}