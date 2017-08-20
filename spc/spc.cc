// spc.cc
// Simple Container
#include <sys/wait.h>    // waitpid
#include <sys/mount.h>   // mount
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
  std::cout << "SPC is starting..." << std::endl;
  Container *container = reinterpret_cast<Container *>(args);
  container->SetConfig();
  std::cout << "Setting config..." << std::endl;
  container->SetRootDir();
  std::cout << "Setting rootfs..." << std::endl;
  container->SetFs();
  std::cout << "Setting some fs..." << std::endl;
  // 对容器进行配置
  // 获取绝对路径命令名字，并调用excl
  /* TODO
  */
  int ret = execl(container->config_.cmd_.c_str(), "bash", NULL);
  std::cout << "SPC is stopping..." << std::endl;
  return ret;
}

void Container::Start() {
  // 创建子进程，并在不同的namespace
  ProcessPid child_pid = clone(SetupContainer, child_stack_ + kStackSize,
      // TODO目前隔离UTS,IPC,PID,NS
      CLONE_NEWUTS | CLONE_NEWIPC | CLONE_NEWPID | CLONE_NEWNS | SIGCHLD,
      this);
  // 等待子进程的推出信号
  waitpid(child_pid, NULL, 0);
}

int Container::SetRootDir() {
  if (chdir(config_.root_dir_.c_str()) != 0) {
    std::cerr << "chdir fails" << std::endl;
    return -1;
  }
  if (chroot(".") != 0) {
    std::cerr << "chroot fails" << std::endl;
    return -1;
  }
  return 0;
}

int Container::SetFs() {
  if (mount("proc", "/proc", "proc", 0, NULL) != 0) {
    std::cerr << "mount /proc fails" << std::endl;
    return -1;
  }
  if (mount("sysfs", "/sys", "sysfs", 0, NULL) != 0) {
    std::cerr << "mount /sys fails" << std::endl;
    return -1;
  }
  if (mount("none", "/tmp", "tmpfs", 0, NULL) != 0) {
    std::cerr << "mount /tmp fails" << std::endl;
    return -1;
  }
  if (mount("udev", "/dev", "devtmpfs", 0, NULL) != 0) {
    std::cerr << "mount /dev fails" << std::endl;
    return -1;
  }
  if (mount("devpts", "/dev/pts", "devpts", 0, NULL) != 0) {
    std::cerr << "mount /dev/pts fails" << std::endl;
    return -1;
  }
  if (mount("shm", "/dev/shm", "tmpfs", 0, NULL) != 0) {
    std::cerr << "mount /dev/shm fails" << std::endl;
    return -1;
  }
  if (mount("tmpfs", "/run", "tmpfs", 0, NULL) != 0) {
    std::cerr << "mount /run fails" << std::endl;
    return -1;
  }
  return 0;
}
} // namespace spc
