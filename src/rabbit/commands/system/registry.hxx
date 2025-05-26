#pragma once
#include "base.hxx"
#include <memory>
#include <string>
#include <unordered_map>

class CommandRegistry {
public:
  static CommandRegistry &instance();

  void add(std::unique_ptr<BaseCommand> command);
  const std::unordered_map<std::string, std::unique_ptr<BaseCommand>> &
  get_all() const;

private:
  std::unordered_map<std::string, std::unique_ptr<BaseCommand>> commands;
};
