#pragma once
#include "base.hxx"

template <typename Derived> class TemplatedCommand : public BaseCommand {
public:
  std::string name() const override {
    return std::string(Derived::metadata.name);
  }

  void register_slash(dpp::cluster &bot, dpp::snowflake guild_id = 0) override {
    dpp::slashcommand cmd(std::string(Derived::metadata.name),
                          std::string(Derived::metadata.description),
                          bot.me.id);
    if (guild_id != 0) {
      bot.guild_command_create(cmd, guild_id);
    } else {
      bot.global_command_create(cmd);
    }
  }

  void execute(const dpp::slashcommand_t &event) override {
    static_cast<Derived *>(this)->handle(event);
  }
};
