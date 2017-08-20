// spc.cc
// Simple Container
#include <sys/wait.h>    // waitpid
#include <unistd.h>      // exec
#include <sched.h>       // clone

#include <string>
#include <iostream>

#include "spc.h"

namespace spc {
// TODO从文件获取配置信息
ContainerConfig::ContainerConfig(const char *config_path) {}

// TODO目前配置不完全
void ContainerConfig::SetContainer() {
  sethostname(host_name_.c_str(), host_name_.length());
}

// TODO
int Container::SetupContainer(void *args) {
  ContainerConfig *config = reinterpret_cast<ContainerConfig *>(args);
  config->SetContainer();
  // 对容器进行配置
  // 获取绝对路径命令名字，并调用excl
  /* TODO
  */
  return execl(config->cmd_.c_str(), "bash", NULL);
}

void Container::Start() {
  // 创建子进程，并在不同的namespace
  ProcessPid child_pid = clone(SetupContainer, child_stack_ + kStackSize,
      // TODO目前隔离UTS,IPC,PID
      CLONE_NEWUTS | CLONE_NEWIPC | CLONE_NEWPID | SIGCHLD,
      &this->config_);
  // 等待子进程的推出信号
  waitpid(child_pid, NULL, 0);
}
} // namespace spc
