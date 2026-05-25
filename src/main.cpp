#include <iostream>
#include <string>
#include <vector>
#include <limits>

#include "log.h"
#include "file_handler.h"
#include "generate_data.h"
#include "benchmark.h"
#include "ds/vector_store.h"
#include "ds/hashmap_store.h"
#include "ds/bst_store.h"

const std::string DATA_FILE = "data/logs.csv";

// ─── Helpers ────────────────────────────────────────────────────────────────

static void printLog(const Log& l) {
    std::cout << "[" << l.id << "] "
              << l.timestamp << " | "
              << l.level     << " | "
              << l.module    << " | "
              << l.message   << "\n";
}

static void printLogs(const std::vector<Log>& logs) {
    if (logs.empty()) { std::cout << "  (no results)\n"; return; }
    for (const auto& l : logs) printLog(l);
    std::cout << "  Total: " << logs.size() << " log(s)\n";
}

static void clearInput() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

// ─── Main ───────────────────────────────────────────────────────────────────

int main() {
    std::cout << "=== Log Monitoring System ===\n";

    // Load all logs from CSV into memory
    std::vector<Log> allLogs = FileHandler::loadFromCSV(DATA_FILE);

    // Load all three data structures
    VectorStore  vs;
    HashMapStore hm;
    BSTStore     bst;

    for (const auto& log : allLogs) {
        vs.insert(log);
        hm.insert(log);
        bst.insert(log);
    }

    int choice = 0;
    while (true) {
        std::cout << "\n--- MENU ---\n"
                  << "1. Insert new log\n"
                  << "2. Search by time range\n"
                  << "3. Search by level (INFO/WARNING/ERROR)\n"
                  << "4. Search by module\n"
                  << "5. Show all ERROR logs\n"
                  << "6. Delete logs before timestamp\n"
                  << "7. Statistics (count per level)\n"
                  << "8. Run benchmark (compare all structures)\n"
                  << "9. Generate new dummy dataset\n"
                  << "0. Save & exit\n"
                  << "Choice: ";
        std::cin >> choice;
        clearInput();

        if (choice == 0) break;

        switch (choice) {

        case 1: {
            Log l;
            std::cout << "Timestamp (YYYY-MM-DD HH:MM:SS): "; std::getline(std::cin, l.timestamp);
            std::cout << "Level (INFO/WARNING/ERROR): ";       std::getline(std::cin, l.level);
            std::cout << "Module: ";                           std::getline(std::cin, l.module);
            std::cout << "Message: ";                          std::getline(std::cin, l.message);
            l.id = static_cast<int>(allLogs.size()) + 1;

            allLogs.push_back(l);
            vs.insert(l);
            hm.insert(l);
            bst.insert(l);
            std::cout << "Inserted log #" << l.id << "\n";
            break;
        }

        case 2: {
            std::string from, to;
            std::cout << "From (YYYY-MM-DD HH:MM:SS): "; std::getline(std::cin, from);
            std::cout << "To   (YYYY-MM-DD HH:MM:SS): "; std::getline(std::cin, to);
            std::cout << "\n[BST result]\n";
            printLogs(bst.searchByTimeRange(from, to));
            break;
        }

        case 3: {
            std::string level;
            std::cout << "Level: "; std::getline(std::cin, level);
            std::cout << "\n[HashMap result]\n";
            printLogs(hm.searchByLevel(level));
            break;
        }

        case 4: {
            std::string mod;
            std::cout << "Module: "; std::getline(std::cin, mod);
            std::cout << "\n[HashMap result]\n";
            printLogs(hm.searchByModule(mod));
            break;
        }

        case 5: {
            std::cout << "\n[HashMap — ERROR logs]\n";
            printLogs(hm.searchByLevel("ERROR"));
            break;
        }

        case 6: {
            std::string cutoff;
            std::cout << "Delete all logs before (YYYY-MM-DD HH:MM:SS): ";
            std::getline(std::cin, cutoff);
            int removed = bst.deleteOlderThan(cutoff);
            std::cout << "Deleted " << removed << " log(s) from BST.\n";
            break;
        }

        case 7: {
            std::cout << "\n--- Statistics ---\n";
            auto stats = hm.statsPerLevel();
            for (const auto& [lvl, cnt] : stats)
                std::cout << "  " << lvl << ": " << cnt << " log(s)\n";
            break;
        }

        case 8: {
            runBenchmark(allLogs);
            break;
        }

        case 9: {
            int n;
            std::cout << "How many logs to generate? "; std::cin >> n; clearInput();
            generateDummyLogs(DATA_FILE, n);
            allLogs = FileHandler::loadFromCSV(DATA_FILE);
            vs = VectorStore();  hm = HashMapStore();  bst = BSTStore();
            for (const auto& log : allLogs) { vs.insert(log); hm.insert(log); bst.insert(log); }
            std::cout << "Dataset reloaded.\n";
            break;
        }

        default:
            std::cout << "Invalid choice.\n";
        }
    }

    FileHandler::saveToCSV(DATA_FILE, allLogs);
    std::cout << "Goodbye.\n";
    return 0;
}
