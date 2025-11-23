#pragma once
#include <memory>
#include <unordered_map>
#include <typeindex>
#include <stdexcept>
using namespace std;

class AppContext {
public:
    template <typename T>
    static void add(T&);

    template <typename T>
    static T& get();

private:
    inline static unordered_map<type_index, void*> _instances;

};

template <typename T>
void AppContext::add(T& instance) {
    _instances[typeid(T)] = &instance;
}

template <typename T>
T& AppContext::get() {
    auto i = _instances.find(type_index(typeid(T)));
    if (i == _instances.end())
        throw runtime_error(string(typeid(T).name()) + " not found in AppContext");
    return *static_cast<T*>(i->second);
}
