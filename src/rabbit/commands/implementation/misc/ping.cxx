#include <misc/ping.hxx>

void PingCommand::handle(const dpp::slashcommand_t &event) {
  event.reply("🏓 Pong!");
}
