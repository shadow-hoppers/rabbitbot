#include "registry.hxx"

CommandRegistry &CommandRegistry::instance() {
  static CommandRegistry inst;
  return inst;
}

void CommandRegistry::add(std::unique_ptr<BaseCommand> command) {
  auto name = command->name();
  commands[name] = std::move(command);
}

const std::unordered_map<std::string, std::unique_ptr<BaseCommand>> &
CommandRegistry::get_all() const {
  return commands;
}
