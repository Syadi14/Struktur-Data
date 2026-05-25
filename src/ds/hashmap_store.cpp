#include "hashmap_store.h"

// O(1) amortized — just appends to two buckets
void HashMapStore::insert(const Log& log) {
    byLevel[log.level].push_back(log);
    byModule[log.module].push_back(log);
    count++;
}

// O(1) lookup — returns the entire bucket for that level
std::vector<Log> HashMapStore::searchByLevel(const std::string& level) const {
    auto it = byLevel.find(level);
    if (it == byLevel.end()) return {};
    return it->second;
}

// O(1) lookup — returns the entire bucket for that module
std::vector<Log> HashMapStore::searchByModule(const std::string& module) const {
    auto it = byModule.find(module);
    if (it == byModule.end()) return {};
    return it->second;
}

// Returns count per level (INFO, WARNING, ERROR)
std::map<std::string, int> HashMapStore::statsPerLevel() const {
    std::map<std::string, int> stats;
    for (const auto& [lvl, logs] : byLevel)
        stats[lvl] = static_cast<int>(logs.size());
    return stats;
}

size_t HashMapStore::size() const { return count; }
