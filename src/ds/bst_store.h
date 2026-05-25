#pragma once
#include <map>
#include <vector>
#include <string>
#include "../log.h"

// std::map is a Red-Black Tree (self-balancing BST) sorted by timestamp
// Time-range search → O(log n) to locate bounds + O(k) to collect results
// Delete old logs → O(log n) per deletion
class BSTStore {
public:
    void              insert(const Log& log);
    std::vector<Log>  searchByTimeRange(const std::string& from, const std::string& to) const;
    int               deleteOlderThan(const std::string& cutoff);
    size_t            size() const;

private:
    // key = "timestamp_id" to allow duplicate timestamps
    std::map<std::string, Log> tree;
};
