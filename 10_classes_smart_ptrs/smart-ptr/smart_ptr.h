#pragma once

#include <string>

class WeakPtr;

class SharedPtr {
   public:
    explicit SharedPtr(const WeakPtr& ptr);
};

class WeakPtr {
   public:
};

inline SharedPtr::SharedPtr(const WeakPtr& ptr) {
}
