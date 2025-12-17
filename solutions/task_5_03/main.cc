#include <algorithm>
#include <cassert>
#include <memory>
#include <print>
#include <string>
#include <vector>

class Unit {
public:
  virtual ~Unit() = default;
  virtual void attack() = 0;
  virtual void move() = 0;
  virtual int get_health() const = 0;
  virtual int get_damage() const = 0;
  virtual std::string get_name() const = 0;
  virtual bool is_composite() const { return false; }
  virtual void add(std::shared_ptr<Unit>) {}
  virtual void remove(std::shared_ptr<Unit>) {}
  virtual std::vector<std::shared_ptr<Unit>> get_children() const { return {}; }
};

class BaseUnit : public Unit {
public:
  BaseUnit(std::string name, int health, int damage)
      : m_name(std::move(name)), m_health(health), m_damage(damage) {}

  void attack() override {
    std::println("{} attacks dealing {} damage", m_name, m_damage);
  }

  void move() override { std::println("{} moves to new position", m_name); }

  int get_health() const override { return m_health; }
  int get_damage() const override { return m_damage; }
  std::string get_name() const override { return m_name; }

protected:
  std::string m_name;
  int m_health;
  int m_damage;
};

class Warrior : public BaseUnit {
public:
  Warrior(std::string name, int health, int damage)
      : BaseUnit(std::move(name), health, damage) {}

  void attack() override {
    std::println("Warrior {} attacks with sword dealing {} damage", m_name,
                 m_damage);
  }
};

class Archer : public BaseUnit {
public:
  Archer(std::string name, int health, int damage)
      : BaseUnit(std::move(name), health, damage) {}

  void attack() override {
    std::println("Archer {} shoots arrow dealing {} damage", m_name, m_damage);
  }
};

class Mage : public BaseUnit {
public:
  Mage(std::string name, int health, int damage)
      : BaseUnit(std::move(name), health, damage) {}

  void attack() override {
    std::println("Mage {} casts spell dealing {} damage", m_name, m_damage);
  }
};

class Army : public Unit {
public:
  explicit Army(std::string name) : m_name(std::move(name)) {}

  void attack() override {
    std::println("Army {} attacks:", m_name);
    for (auto &unit : m_units) {
      unit->attack();
    }
  }

  void move() override {
    std::println("Army {} moves:", m_name);
    for (auto &unit : m_units) {
      unit->move();
    }
  }

  int get_health() const override {
    int total = 0;
    for (const auto &unit : m_units) {
      total += unit->get_health();
    }
    return total;
  }

  int get_damage() const override {
    int total = 0;
    for (const auto &unit : m_units) {
      total += unit->get_damage();
    }
    return total;
  }

  std::string get_name() const override { return m_name; }
  bool is_composite() const override { return true; }

  void add(std::shared_ptr<Unit> unit) override {
    m_units.push_back(std::move(unit));
  }

  void remove(std::shared_ptr<Unit> unit) override {
    m_units.erase(std::remove(m_units.begin(), m_units.end(), unit),
                  m_units.end());
  }

  std::vector<std::shared_ptr<Unit>> get_children() const override {
    return m_units;
  }

private:
  std::string m_name;
  std::vector<std::shared_ptr<Unit>> m_units;
};

class UnitBuilder {
public:
  UnitBuilder &set_name(std::string name) {
    m_name = std::move(name);
    return *this;
  }

  UnitBuilder &set_health(int health) {
    m_health = health;
    return *this;
  }

  UnitBuilder &set_damage(int damage) {
    m_damage = damage;
    return *this;
  }

  std::shared_ptr<Warrior> build_warrior() const {
    return std::make_shared<Warrior>(m_name, m_health, m_damage);
  }

  std::shared_ptr<Archer> build_archer() const {
    return std::make_shared<Archer>(m_name, m_health, m_damage);
  }

  std::shared_ptr<Mage> build_mage() const {
    return std::make_shared<Mage>(m_name, m_health, m_damage);
  }

private:
  std::string m_name;
  int m_health{100};
  int m_damage{10};
};

class BattleStrategy {
public:
  virtual ~BattleStrategy() = default;

  void execute_battle(Unit &attacker, Unit &defender) {
    prepare_battle();
    perform_attack(attacker);
    perform_defense(defender);
    conclude_battle();
  }

protected:
  virtual void prepare_battle() { std::println("Battle preparation phase"); }

  virtual void perform_attack(Unit &attacker) = 0;
  virtual void perform_defense(Unit &defender) = 0;

  virtual void conclude_battle() { std::println("Battle concluded"); }
};

class AggressiveStrategy : public BattleStrategy {
protected:
  void perform_attack(Unit &attacker) override {
    std::println("Aggressive attack:");
    attacker.attack();
    attacker.attack();
  }

  void perform_defense(Unit &defender) override {
    std::println("Minimal defense:");
    defender.move();
  }
};

class DefensiveStrategy : public BattleStrategy {
protected:
  void perform_attack(Unit &attacker) override {
    std::println("Cautious attack:");
    attacker.attack();
  }

  void perform_defense(Unit &defender) override {
    std::println("Strong defense:");
    defender.move();
    defender.move();
  }
};

int main() {
  UnitBuilder builder;

  auto warrior =
      builder.set_name("Knight").set_health(150).set_damage(20).build_warrior();
  auto archer =
      builder.set_name("Ranger").set_health(100).set_damage(15).build_archer();
  auto mage =
      builder.set_name("Wizard").set_health(80).set_damage(30).build_mage();

  assert(warrior->get_name() == "Knight");
  assert(warrior->get_health() == 150);
  assert(warrior->get_damage() == 20);

  auto army1 = std::make_shared<Army>("Legion");
  army1->add(warrior);
  army1->add(archer);
  army1->add(mage);

  assert(army1->get_health() == 330);
  assert(army1->get_damage() == 65);
  assert(army1->is_composite());

  army1->attack();
  army1->move();

  auto enemy_warrior =
      builder.set_name("Orc").set_health(120).set_damage(18).build_warrior();

  AggressiveStrategy aggressive;
  aggressive.execute_battle(*warrior, *enemy_warrior);

  DefensiveStrategy defensive;
  defensive.execute_battle(*archer, *enemy_warrior);

  std::println("\nAll good");
}
