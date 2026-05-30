#include "bst_store.h"

// Key = "timestamp_id" so logs with identical timestamps don't overwrite each other
void BSTStore::insert(const Log& log) {
    std::string key = log.timestamp + "_" + std::to_string(log.id);
    tree[key] = log;
}

// lower_bound / upper_bound = O(log n), traversal = O(k results)
std::vector<Log> BSTStore::searchByTimeRange(const std::string& from, const std::string& to) const {
    std::vector<Log> result;

    // lower_bound gives first key >= "from"
    auto it    = tree.lower_bound(from);
    // upper_bound gives first key >  "to_~" (tilde sorts after any digit/letter)
    auto itEnd = tree.upper_bound(to + "~");

    for (; it != itEnd; ++it)
        result.push_back(it->second);

    return result;
}

// Erases all entries with timestamp < cutoff — O(k log n)
int BSTStore::deleteOlderThan(const std::string& cutoff) {
    auto it  = tree.begin();
    auto end = tree.lower_bound(cutoff);
    int count = static_cast<int>(std::distance(it, end));
    tree.erase(it, end);
    return count;
}

size_t BSTStore::size() const { return tree.size(); }
