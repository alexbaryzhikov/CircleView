#ifndef AutoRelease_hpp
#define AutoRelease_hpp

#include <iostream>
#include <cxxabi.h>

template<typename T>
std::unique_ptr<char, void(*)(void*)> typeName() {
    int status = 0;
    const char* mangled_name = typeid(T).name();
    char* demangled_name = abi::__cxa_demangle(mangled_name, nullptr, nullptr, &status);
    return std::unique_ptr<char, void(*)(void*)>(demangled_name, std::free);
}

template<typename T>
std::shared_ptr<T> sharedPtr(T* resource, NS::Error** error = nullptr) {
    if (!resource) {
        std::cerr << "Couldn't create " << typeName<T>().get();
        if (error && *error) {
            std::cerr << ": " << (*error)->localizedDescription()->utf8String();
        }
        std::cerr << '\n';
        assert(false);
    }
    return std::shared_ptr<T>(resource, [](T* resource){ resource->release(); });
}

#endif /* AutoRelease_hpp */
