## Remote Shutdown

这是一个简单的关机服务器，在服务器端`Linux`编译并运行`listener.cpp`文件，在客户端`Win/Linux`编译并运行`sd.cpp`，便可实现远程关机。

### Server

编译指令：
```bash
g++ -g listener.cpp -o listener
```
运行（关机需要管理员权限）
```bash
sudo ./listener
```

若以服务开机启动

在`/etc/systemd/system/`创建`listener.service`
写入
```
[Unit]  
Description=Listener Service  
After=network.target  
  
[Service]  
ExecStart=这里填写listener路径
Restart=always  
User=root  
  
[Install]  
WantedBy=multi-user.target
```

保存并退出，更新服务

```bash
sudo systemctl daemon-reload
```

然后你可以

```bash
sudo systemctl start listener.service   # 启动服务  
sudo systemctl stop listener.service    # 停止服务  
sudo systemctl restart listener.service  # 重启服务
sudo systemctl enable listener.service  # 开机自启
```

### Client

- Windows
  编译指令(`MinGW`编译器)
  ```
  g++ -g sd.cpp -o sd.exe -lwsock32
  ```
- Linux
  编译指令
  ```
  g++ -g sd.cpp -o sd
  ```