## Wireshark

>  The world's most popular network protocol analyzer

[Wireshark tool download](https://www.wireshark.org/#downloadLink)

### Step
- 选择网卡名称, 双击进入抓包页面, 每一行是一个数据包
- 过滤规则: 规则正确,过滤栏显示绿色; 规则有错误,过滤栏显示红色提示;
    1. 按照IP地址过滤
    2. 按照MAC地址过滤
    3. 按照端口号过滤
    4. 按照协议类型过滤
    5. 按照 组合规则 进行过滤
```shell
# ==========0. 查看电脑的网络相关信息
ipconfig -all

# ==========1. 按照IP地址过滤
# 只看源IP地址为: 192.168.250.1 的数据包
ip.src==192.168.250.1

# 只看目标IP地址为: 192.168.250.1 的数据包
ip.dst==192.168.250.1

# 只看IP地址为: 192.168.250.1 的数据包
ip.addr==192.168.250.1

# ==========2. 按照MAC地址过滤
# 只看源MEC地址为: 192.168.250.1 的数据包
eth.src==00-50-56-C0-10-07

# 只看目标MAC地址为: 00-50-56-C0-10-07 的数据包
eth.dst==00-50-56-C0-10-07

# 只看MAC地址为: 00-50-56-C0-10-07 的数据包
eth.addr==00-50-56-C0-10-07

# ==========3. 按照端口号过滤
# 只看TCP/UDP源端口号为: 21 的数据包
tcp.srcport==21
upd.srcport==21

# 只看TCP/UDP目标端口号为: 21 的数据包
tcp.dstport==21
udp.dstport==21

# 只看TCP/UDP端口号为: 21 的数据包
tcp.port==21
udp.port==21

# ==========4. 按照协议类型过滤
# 只看 arp/dns/ 协议类型的数据包
arp
dns
dhcp
ftp
tftp

# ==========5. 按照 组合规则 进行过滤
# and 组合
dhcp and eth.addr==00-50-56-C0-10-07
# or 组合
dhcp or arp
# not(非) 组合
!arp

```
