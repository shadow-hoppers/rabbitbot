#include <rabbit/commands.hxx>
#include <rabbit/core.hxx>

using json = nlohmann::json;

json load_config(const std::string &path) {
  std::ifstream file(path);
  if (!file.is_open()) {
    throw std::runtime_error("Could not open file: " + path);
  }

  json j;
  file >> j;
  return j;
}

int main() {
  json config;

  try {
    config = load_config("../../../../botconfig.json"); /* For `xmake run` */
  } catch (...) {
    try {
      config = load_config("./botconfig.json");
    } catch (const std::exception &e) {
      std::cerr << "Failed to load config: " << e.what() << '\n';
      return 1;
    }
  }
  const std::string log_name = config["Log_File"];

  dpp::cluster bot(config["Bot_Token"]);

  std::shared_ptr<spdlog::logger> log;
  spdlog::init_thread_pool(8192, 2);
  std::vector<spdlog::sink_ptr> sinks;
  auto stdout_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
  auto rotating = std::make_shared<spdlog::sinks::rotating_file_sink_mt>(
      log_name, 1024 * 1024 * 5, 10);
  sinks.push_back(stdout_sink);
  sinks.push_back(rotating);

  log = std::make_shared<spdlog::async_logger>(
      "logs", sinks.begin(), sinks.end(), spdlog::thread_pool(),
      spdlog::async_overflow_policy::block);
  spdlog::register_logger(log);
  log->set_pattern("%^%Y-%m-%d %H:%M:%S.%e [%L] [Thread/%t]%$ : %v");
  log->set_level(spdlog::level::level_enum::debug);

  bot.on_log([&bot, &log](const dpp::log_t &event) {
    switch (event.severity) {
    case dpp::ll_trace:
      log->trace("{}", event.message);
      break;
    case dpp::ll_debug:
      log->debug("{}", event.message);
      break;
    case dpp::ll_info:
      log->info("{}", event.message);
      break;
    case dpp::ll_warning:
      log->warn("{}", event.message);
      break;
    case dpp::ll_error:
      log->error("{}", event.message);
      break;
    case dpp::ll_critical:
    default:
      log->critical("{}", event.message);
      break;
    }
  });
  dpp::snowflake dev_guild_id =
      static_cast<dpp::snowflake>(config["Slash_Guilds"].get<uint64_t>());

  bot.on_ready([&](const dpp::ready_t &event) {
    log->info("Bot is ready.");
    log->info("Bot user: {}.", bot.me.username);
    log->info("Is dev mode? (0 is production): {}.", dev_guild_id);
    if (dpp::run_once<struct register_commands>()) {
      for (auto &[_, cmd] : CommandRegistry::instance().get_all()) {
        cmd->register_slash(bot, dev_guild_id);
      }
    }
  });

  bot.on_slashcommand([&](const dpp::slashcommand_t &event) {
    auto &cmds = CommandRegistry::instance().get_all();
    auto it = cmds.find(event.command.get_command_name());
    if (it != cmds.end()) {
      it->second->execute(event);
    }
  });

  bot.start(dpp::st_wait);
}
