#include <cassert>
#include <print>
#include <string>

class Person {
public:
    Person() = default;
    
    Person(std::string name, int age, int grade)
        : m_name(std::move(name)), m_age(age), m_grade(grade) {}
    
    const std::string& name() const { return m_name; }
    int age() const { return m_age; }
    int grade() const { return m_grade; }

private:
    std::string m_name;
    int m_age{0};
    int m_grade{0};
};

class Builder {
public:
    Builder() = default;
    
    Builder& name(std::string value) {
        m_name = std::move(value);
        return *this;
    }
    
    Builder& age(int value) {
        m_age = value;
        return *this;
    }
    
    Builder& grade(int value) {
        m_grade = value;
        return *this;
    }
    
    Person get() const {
        return Person(m_name, m_age, m_grade);
    }

private:
    std::string m_name;
    int m_age{0};
    int m_grade{0};
};

int main() {
    Builder builder;
    
    auto person1 = builder.name("Ivan").age(25).grade(10).get();
    assert(person1.name() == "Ivan");
    assert(person1.age() == 25);
    assert(person1.grade() == 10);
    
    auto person2 = Builder().name("Maria").age(30).grade(12).get();
    assert(person2.name() == "Maria");
    assert(person2.age() == 30);
    assert(person2.grade() == 12);
    
    auto person3 = Builder().age(20).name("Alex").grade(9).get();
    assert(person3.name() == "Alex");
    assert(person3.age() == 20);
    assert(person3.grade() == 9);
    
    auto person4 = Builder().grade(11).get();
    assert(person4.name() == "");
    assert(person4.age() == 0);
    assert(person4.grade() == 11);
    
    std::println("All good");
    std::println("Person: name={}, age={}, grade={}", person1.name(), person1.age(), person1.grade());
}
