#pragma once
#include <dpp/dpp.h>

class BaseCommand {
public:
  virtual ~BaseCommand() = default;
  virtual std::string name() const = 0;
  virtual void register_slash(dpp::cluster& bot, dpp::snowflake guild_id = 0) = 0;
  virtual void execute(const dpp::slashcommand_t &event) = 0;
};
