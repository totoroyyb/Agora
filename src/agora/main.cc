/**
 * @file main.cc
 * @brief Main file for the agora server
 */
#include "agora.h"
#include "gflags/gflags.h"
#include "logger.h"
#include "signal_handler.h"
#include "version_config.h"

DEFINE_string(
    conf_file,
    TOSTRING(PROJECT_DIRECTORY) "/files/config/ci/tddconfig-sim-both.json",
    "Config filename");

int main(int argc, char* argv[]) {
  gflags::SetUsageMessage("conf_file : set the configuration filename");
  gflags::SetVersionString(GetAgoraProjectVersion());
  gflags::ParseCommandLineFlags(&argc, &argv, true);

  AGORA_LOG_INIT();
  std::string conf_file;

  // For backwards compatibility
  if (argc == 2) {
    conf_file = std::string(argv[1]);
    std::printf("User: Setting configuration filename to %s\n",
                conf_file.c_str());
  } else {
    conf_file = FLAGS_conf_file;
  }
  std::printf("conf_file: %s\n", conf_file.c_str());
  std::unique_ptr<Config> cfg = std::make_unique<Config>(conf_file.c_str());
  cfg->GenData();

  std::printf("Started core assignment.\n");
  int ret;
  try {
    SignalHandler signal_handler;

    // Register signal handler to handle kill signal
    std::printf("Started to register signal handler.\n");
    signal_handler.SetupSignalHandlers();
    std::printf("Finished register signal handler.\n");
    std::unique_ptr<Agora> agora_cli = std::make_unique<Agora>(cfg.get());
    std::printf("Finished init agora cli.\n");
    agora_cli->Start();
    std::printf("Started agora cli.\n");
    ret = EXIT_SUCCESS;
  } catch (SignalException& e) {
    std::cerr << "SignalException: " << e.what() << std::endl;
    ret = EXIT_FAILURE;
  }
  std::printf("Finished core assignment.\n");
  PrintCoreAssignmentSummary();
  gflags::ShutDownCommandLineFlags();
  AGORA_LOG_SHUTDOWN();

  return ret;
}
