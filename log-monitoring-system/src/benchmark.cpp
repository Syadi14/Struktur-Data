#include "benchmark.h"
#include "ds/vector_store.h"
#include "ds/hashmap_store.h"
#include "ds/bst_store.h"
#include <chrono>
#include <iostream>
#include <iomanip>

using Clock = std::chrono::high_resolution_clock;
using Ms    = std::chrono::duration<double, std::milli>;

static double elapsed(Clock::time_point start) {
    return Ms(Clock::now() - start).count();
}

void runBenchmark(const std::vector<Log>& logs) {
    std::cout << "\n========== BENCHMARK (" << logs.size() << " logs) ==========\n";
    std::cout << std::left
              << std::setw(20) << "Operation"
              << std::setw(14) << "Vector(ms)"
              << std::setw(14) << "HashMap(ms)"
              << std::setw(14) << "BST(ms)"
              << "\n"
              << std::string(62, '-') << "\n";

    // ── INSERT ──────────────────────────────────────────────
    VectorStore  vs; HashMapStore hm; BSTStore bst;

    auto t = Clock::now();
    for (const auto& l : logs) vs.insert(l);
    double vsIns = elapsed(t);

    t = Clock::now();
    for (const auto& l : logs) hm.insert(l);
    double hmIns = elapsed(t);

    t = Clock::now();
    for (const auto& l : logs) bst.insert(l);
    double bstIns = elapsed(t);

    std::cout << std::setw(20) << "Insert all"
              << std::setw(14) << vsIns
              << std::setw(14) << hmIns
              << std::setw(14) << bstIns << "\n";

    // ── SEARCH by level ─────────────────────────────────────
    t = Clock::now(); vs.searchByLevel("ERROR");  double vsLvl = elapsed(t);
    t = Clock::now(); hm.searchByLevel("ERROR");  double hmLvl = elapsed(t);

    std::cout << std::setw(20) << "Search by level"
              << std::setw(14) << vsLvl
              << std::setw(14) << hmLvl
              << std::setw(14) << "N/A" << "\n";

    // ── SEARCH by time range ─────────────────────────────────
    t = Clock::now(); vs.searchByTimeRange("2024-06-01 00:00:00", "2024-06-30 23:59:59"); double vsT = elapsed(t);
    t = Clock::now(); bst.searchByTimeRange("2024-06-01 00:00:00", "2024-06-30 23:59:59"); double bstT = elapsed(t);

    std::cout << std::setw(20) << "Search time range"
              << std::setw(14) << vsT
              << std::setw(14) << "N/A"
              << std::setw(14) << bstT << "\n";

    // ── DELETE old logs ──────────────────────────────────────
    t = Clock::now(); vs.deleteOlderThan("2024-06-01 00:00:00");  double vsDel = elapsed(t);
    t = Clock::now(); bst.deleteOlderThan("2024-06-01 00:00:00"); double bstDel = elapsed(t);

    std::cout << std::setw(20) << "Delete old logs"
              << std::setw(14) << vsDel
              << std::setw(14) << "N/A"
              << std::setw(14) << bstDel << "\n";

    std::cout << std::string(62, '-') << "\n";
    std::cout << "N/A = operation not the strength of that structure\n";
    std::cout << "======================================================\n";
}
