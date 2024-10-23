#ifdef __cplusplus
extern "C" {
#endif

#include <queue>
#include <cstddef>
#include <vector>
#include <iostream>

#ifdef NDEBUG
constexpr bool DEBUG = true;
#else
constexpr bool DEBUG = false;
#endif

vector <vector <string>> container;
vector <bool> deleted;
queue <unsigned long> reusable;

unsigned long strqueue_new() {
    if constexpr (DEBUG) {
        std::cerr << "strqueue_new()" << std::endl;
    }

    if (reusable.empty()) {
        container.push_back ({});
        deleted.push_back (false);
        return container.size() - 1;
    }
    unsigned long new_id = reusable.front();
    reusable.pop();
    deleted[new_id] = false;

    if constexpr (DEBUG) {
    std::cerr << "strqueue_new returns " << new_id << std::endl;
    }

    return new_id;
}

void strqueue_delete(unsigned long id) {
    if constexpr (DEBUG) {
    std::cerr << "strqueue_delete(" << id << ")" << std::endl;
    }

    if (id >= container.size() || deleted[id] == true) {
        if constexpr (DEBUG) {
        std::cerr << "strqueue_delete: there is no queue of id " << id << std::endl;
    }
        return;
    }

    container[id].clear();
    deleted[id] = true;
    reusable.push(id);

    if constexpr (DEBUG) {
    std::cerr << "strqueue_delete done" << std::endl;
    }
}

size_t strqueue_size(unsigned long id) {
    if (id >= container.size()) return 0;
    return container[id].size(); 
}

void strqueue_insert_at(unsigned long id, size_t position, const char* str) {
    if (id >= container.size() || position > container[id].size() || str == NULL) return;
    container[id].insert(container[id].begin() + position, str);
}

void strqueue_remove_at(unsigned long id, size_t position) {
    if (id >= container.size() || position >= container[id].size()) return;
    container[id].erase(container[id].begin() + position);
}

const char* strqueue_get_at(unsigned long id, size_t position) {
    if (id >= container.size() || position >= container[id].size()) return NULL;
    return container[id][position];
}

void strqueue_clear(unsigned long id) {
    if (id >= container.size() || deleted[id] == true) return;
    container[id].clear();
}

int strqueue_comp(unsigned long id1, unsigned long id2) {
    if (container[id1] < container[id2]) return -1;
    else if (container[id1] == container[id2]) return 0;
    return 1;
}

#ifdef __cplusplus
}
#endif
