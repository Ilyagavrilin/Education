#include <cassert>
#include <print>
#include <string>

class AggressiveStrategy {
public:
  std::string execute() const { return "Aggressive attack with full force"; }

  int get_damage_multiplier() const { return 2; }
};

class DefensiveStrategy {
public:
  std::string execute() const { return "Defensive maneuver with caution"; }

  int get_damage_multiplier() const { return 1; }
};

class BalancedStrategy {
public:
  std::string execute() const { return "Balanced approach with tactics"; }

  int get_damage_multiplier() const { return 3; }
};

template <typename Strategy> class Entity : public Strategy {
public:
  Entity(std::string name, int base_damage)
      : m_name(std::move(name)), m_base_damage(base_damage) {}

  void attack() const {
    std::println("{} performs: {}", m_name, Strategy::execute());
    std::println("Total damage: {}", get_total_damage());
  }

  int get_total_damage() const {
    return m_base_damage * Strategy::get_damage_multiplier();
  }

  std::string get_name() const { return m_name; }

private:
  std::string m_name;
  int m_base_damage;
};

int main() {
  Entity<AggressiveStrategy> warrior("Warrior", 10);
  assert(warrior.get_name() == "Warrior");
  assert(warrior.get_total_damage() == 20);
  assert(warrior.execute() == "Aggressive attack with full force");

  Entity<DefensiveStrategy> knight("Knight", 15);
  assert(knight.get_name() == "Knight");
  assert(knight.get_total_damage() == 15);
  assert(knight.execute() == "Defensive maneuver with caution");

  Entity<BalancedStrategy> mage("Mage", 8);
  assert(mage.get_name() == "Mage");
  assert(mage.get_total_damage() == 24);
  assert(mage.execute() == "Balanced approach with tactics");

  warrior.attack();
  std::println("");
  knight.attack();
  std::println("");
  mage.attack();

  std::println("\nAll good");
}
