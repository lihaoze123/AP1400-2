#ifndef UNIQUE_PTR
#define UNIQUE_PTR

template <typename T>
class UniquePtr {
private:
    T* _p = nullptr;

public:
    UniquePtr() = default;
    UniquePtr(T* _p): _p(_p) {}

    T* get() {
        return _p;
    }

    T& operator * () {
        return *_p;
    }

    T* operator -> () {
        return _p;
    }
};

template <typename T>
UniquePtr<T> make_unique(T&& _p) {
    return UniquePtr<T>{&_p};
}

#endif //UNIQUE_PTR
