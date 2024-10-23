#include <queue>
#include <cstddef>
#include <vector>
#include <iostream>

using namespace std;

namespace 
{
    #ifdef NDEBUG
    constexpr bool debug = true;
    #else
    constexpr bool debug = false;
    #endif

    template<class ...Args>
    void _log_call(const std::string& name, const Args&... args)
    {
        if constexpr (!debug)
            return;

        bool comma = false;
        std::cerr << name << "(";
        ( (
            if (nocomma)
                std::cerr << ", ";
            else
                nocomma = true;
            std::cerr << args
        ), ...);
        std::cerr << std::endl;
    }

    #define log_call(...) _log_call(__func__ __VA_OPT__(,) __VA_ARGS__)

    template<class T>
    void _log_returns(const std::string& name, const T& value)
    {
        if constexpr (!debug) 
            return;

        std::cerr << name << " returns " << value << std::endl;
    }

    void _log_returns(const std::string& name)
    {
        if constexpr (!debug) 
            return;

        std::cerr << name << " done" << std::endl;
    }

    #define log_returns(...) _log_returns(__func__ __VA_OPT__(,) __VA_ARGS__)
    
    void _log_error(const std::string& name, const std::string& message = "")
    {
        if constexpr (!debug) 
            return;
        
        std::cerr << name << ": " << message << std::endl;
    }

    #define log_error(...) _log_error(__func__ __VA_OPT__(,) __VA_ARGS__)
}

vector <vector <string>> container;
vector <bool> deleted;
queue <unsigned long> reusable;

unsigned long strqueue_new() {
    log_call();

    if (reusable.empty()) {
        container.push_back ({});
        deleted.push_back (false);
        
        log_returns(container.size() - 1);
        return container.size() - 1;
    }
    unsigned long new_id = reusable.front();
    reusable.pop();
    deleted[new_id] = false;

    log_returns(new_id);
    return new_id;
}

void strqueue_delete(unsigned long id) {
    if constexpr (debug) {
        log_call(id);
    }

    if (id >= container.size() || deleted[id] == true) {
        log_error("there is no queue of index"+std::to_string(id));
        return;
    }

    container[id].clear();
    deleted[id] = true;
    reusable.push(id);

    log_returns();
}

size_t strqueue_size(unsigned long id) {
    if (id >= container.size()) return 0;
    return container[id].size(); 
}

void strqueue_insert_at(unsigned long id, size_t position, const char* str) {
    if constexpr (debug) {
        std::cerr << "strqueue_insert_at(" << id << ", " << 0, "a")d " << id << std::endl;
    }

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
