// spc.h
// simple container
#ifndef SPC_SPC_H_
#define SPC_SPC_H_

#include <string>

namespace spc {
const int kStackSize = 512 * 512;

// 容器启动时的配置
class ContainerConfig {
 public:
  explicit ContainerConfig(const char *config_path);
  // 加载配置文件
  void LoadConfig();
  // 配置到容器
  void SetContainer();

  // 配置文件路径
  std::string config_path_;
  // 主机名
  std::string host_name_ = "spc_host";
  // TODO用户名，应该无法直接修改用户
  // 这里需要实现把普通用户映射成root
  // 根目录
  std::string root_dir_ = "./rootfs";
  // 容器执行命令
  std::string cmd_ = "/bin/bash";
};

// 容器类
class Container {
 public:
  // 配置文件初始化容器
  explicit Container(const char *config_path) : config_(config_path) {}
  // 创建namespace启动容器
  void Start();
  // 根据配置，运行进程
  static int SetupContainer(void *args);
  // 把配置设置到容器
  void SetConfig() { config_.SetContainer(); }
  // 设置根目录
  int SetRootDir();
  // 设置fs
  int SetFs();
 private:
  typedef int ProcessPid;
  // 子进程的栈
  char child_stack_[kStackSize];
  // 容器配置
  ContainerConfig config_;
};
} // namespace spc
#endif // SPC_SPC_H_
