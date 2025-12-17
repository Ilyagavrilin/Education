#include <cassert>
#include <print>
#include <string>

class Entity {
public:
    virtual ~Entity() = default;
    virtual std::string get() const = 0;
};

class Basic : public virtual Entity {
public:
    std::string get() const override {
        return "Basic";
    }
};

template<typename T>
class Decorator : public virtual Entity, public T {
public:
    std::string get() const override {
        return T::get() + " + Decorator";
    }
};

class Feature1 : public virtual Entity {
public:
    std::string get() const override {
        return "Feature1";
    }
};

class Feature2 : public virtual Entity {
public:
    std::string get() const override {
        return "Feature2";
    }
};

template<typename T>
class DecoratorA : public virtual Entity, public T {
public:
    std::string get() const override {
        return T::get() + " + A";
    }
};

template<typename T>
class DecoratorB : public virtual Entity, public T {
public:
    std::string get() const override {
        return T::get() + " + B";
    }
};

int main() {
    Basic basic;
    assert(basic.get() == "Basic");
    
    Decorator<Basic> decorated_basic;
    assert(decorated_basic.get() == "Basic + Decorator");
    
    Decorator<Decorator<Basic>> double_decorated;
    assert(double_decorated.get() == "Basic + Decorator + Decorator");
    
    DecoratorA<Basic> decorated_a;
    assert(decorated_a.get() == "Basic + A");
    
    DecoratorB<DecoratorA<Basic>> decorated_ab;
    assert(decorated_ab.get() == "Basic + A + B");
    
    DecoratorA<DecoratorB<Basic>> decorated_ba;
    assert(decorated_ba.get() == "Basic + B + A");
    
    std::println("All good");
    std::println("Basic: {}", basic.get());
    std::println("Decorated: {}", decorated_basic.get());
    std::println("Double decorated: {}", double_decorated.get());
    std::println("A-B decorated: {}", decorated_ab.get());
}
