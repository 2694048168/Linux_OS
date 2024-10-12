#!/usr/bin/env python3
# -*- coding: utf-8 -*-

"""
@File: performance_monitor.py
@Python Version: 3.12.1
@Platform: PyTorch 2.2.1 + cu121
@Author: Wei Li (Ithaca)
@Date: 2024-10-09.
@Contact: weili_yzzcq@163.com
@Blog: https://2694048168.github.io/blog/#/
@Version: V2.1
@License: Apache License Version 2.0, January 2004
    Copyright 2024. All rights reserved.

@Command: pip install psutil
@Doc: https://hellowac.github.io/psutil-doc-zh/guide/install.html
@Doc: https://psutil.readthedocs.io/en/latest/#id1
@Logger: https://github.com/delgan/loguru
@Logger: https://www.cnblogs.com/Nephalem-262667641/p/17475549.html
@Description: 实时监控并采集工控机性能参数, 同步监控并采集进程资源占用
"""

import os
import sys  # len(sys.argv) and sys.argv[1]
import logging
import argparse  # command line args parse
import time
import datetime
import asyncio
import psutil
import matplotlib.pyplot as plt


# Python 异步协程
async def monitor_io(process_id, duration):
    process = psutil.Process(process_id)
    start_time = time.time()

    while time.time() - start_time < duration:
        io_counters = process.io_counters()
        print(f"读取字节数: {io_counters.read_bytes / 1024 / 1024} MB")
        print(f"写入字节数: {io_counters.write_bytes / 1024 / 1024} MB")
        await asyncio.sleep(1)


async def monitor_memory(process_id, duration):
    process = psutil.Process(process_id)
    start_time = time.time()

    while time.time() - start_time < duration:
        memory_info = process.memory_info()
        memory_percent = process.memory_percent()
        print(f"内存使用量: {memory_info.rss / (1024 * 1024):.2f} MB")
        print(f"内存使用率: {memory_percent:.2f}%")
        await asyncio.sleep(1)


async def monitor_cpu(process_id, duration):
    process = psutil.Process(process_id)
    start_time = time.time()

    while time.time() - start_time < duration:
        cpu_percent = process.cpu_percent(interval=1)
        print(f"CPU 使用率: {cpu_percent}%")
        await asyncio.sleep(1)


def start_process():
    p = psutil.Process(16031)
    p.name()  # 进程名
    p.exe()  # 进程的bin路径
    p.cwd()  # 进程的工作目录绝对路径
    p.status()  # 进程状态
    p.create_time()  # 进程创建时间
    p.uids()  # 进程uid信息
    p.gids()  # 进程的gid信息
    p.cpu_times()  # 进程的cpu时间信息,包括user,system两个cpu信息
    p.cpu_affinity()  # get进程cpu亲和度,如果要设置cpu亲和度,将cpu号作为参考就好
    p.memory_percent()  # 进程内存利用率
    p.memory_info()  # 进程内存rss,vms信息
    p.io_counters()  # 进程的IO信息,包括读写IO数字及参数
    p.connectios()  # 返回进程列表
    p.num_threads()  # 进程开启的线程数
    # 听过psutil的Popen方法启动应用程序，可以跟踪程序的相关信息
    from subprocess import PIPE

    p = psutil.Popen(["/usr/bin/python", "-c", "print('hello')"], stdout=PIPE)
    p.name()
    p.username()


class MonitorPerformance(object):
    """实时监控并采集工控机性能参数, 同步监控并采集进程资源占用.
    @Function 1: logging into console and log-file;
    @Function 2: performance params(CPU/Memory/Disk and Network IO) write into CSV;
    @Function 3: after stop monitor auto Statistics(measure) and Analysis(plot);
    @Function 4: System-wide and Process-wide monitor;
    """

    def __init__(self, process_name, log_dir="./logs/"):
        self.log_dir = log_dir
        os.makedirs(self.log_dir, exist_ok=True)

        self.process_name = process_name
        self.process_id = -1
        # 根据进程名称获取对应的进程PID
        pids = psutil.process_iter()
        for pid in pids:
            if pid.name() == self.process_name:
                self.process_id = pid.pid

        self.interval_epoch = 3  # polling seconds to write data to file

        # 获取所有进程列表
        all_processes = psutil.process_iter(attrs=["pid", "name"])
        for process in all_processes:
            print(f"Process ID: {process.info['pid']}, Name: {process.info['name']}")

        # 根据进程名称查询进程
        process_name = "python3"
        process_list = [p.info for p in all_processes if p.info["name"] == process_name]
        for process in process_list:
            print(f"Process ID: {process['pid']}, Name: {process['name']}")

    @staticmethod
    def DefectingSystem():
        # ============ CPU ============
        # get the CPU Physical core number
        cpu_core_num = psutil.cpu_count(logical=False)
        # get the CPU Logical core number, include the super-thread
        cpu_logical_num = psutil.cpu_count(logical=True)

        # get the CPU per-core percent of total system
        cpu_usage_list = psutil.cpu_percent(interval=1, percpu=True)
        for idx, usage in enumerate(cpu_usage_list):
            str = f"CPU-core num {idx} usage ---> {usage}%\n"
        cpu_usage_total = psutil.cpu_percent(interval=1, percpu=False)

        # ============ Memory ============
        # get the memory-total: total physical memory (exclusive swap).
        total_memory = psutil.virtual_memory().total
        str_totalMem_GB = f"Total Memory ---> {total_memory / (1024 **3):.4f} GB"
        print(str_totalMem_GB)

        # get the available memory: the memory that can be given instantly to processes without the system going into swap.
        available_memory = psutil.virtual_memory().available
        str_availableMem_GB = (
            f"Total Memory ---> {available_memory / (1024 **3):.4f} GB"
        )
        print(str_availableMem_GB)

        # get the memory-percent: the percentage usage calculated as (total - available) / total * 100.
        memory_usage = psutil.virtual_memory().percent

        # ============ Disks ============
        # 获取所有磁盘分区信息
        disk_partitions = psutil.disk_partitions()
        for partition in disk_partitions:
            print(f"Device: {partition.device}")
            print(f"Mountpoint: {partition.mountpoint}")
            print(f"Fstype: {partition.fstype}")
            print("")

        # 获取指定分区的使用情况
        disk_usage = psutil.disk_usage("/")
        print(f"Total: {disk_usage.total / (1024 ** 3):.2f} GB")
        print(f"Used: {disk_usage.used / (1024 ** 3):.2f} GB")
        print(f"Free: {disk_usage.free / (1024 ** 3):.2f} GB")
        print(f"Usage: {disk_usage.percent}%")

        # 监控磁盘IO
        for _ in range(5):
            disk_io = psutil.disk_io_counters()
            print(
                f"Read Count: {disk_io.read_count} and the Read Bytes: {disk_io.read_bytes}"
            )
            print(
                f"Write Count: {disk_io.write_count} and the Write Bytes: {disk_io.write_bytes}"
            )
            time.sleep(1)

        # ============ Network ============
        # 获取网络接口列表
        network_interfaces = psutil.net_if_addrs()
        for interface, addresses in network_interfaces.items():
            print(f"Interface: {interface}")
            for address in addresses:
                print(f"  Family: {address.family}")
                print(f"  Address: {address.address}")
                print(f"  Netmask: {address.netmask}")
                print(f"  Broadcast: {address.broadcast}")
            print("")

        # 监控网络流量
        for _ in range(5):
            network_io = psutil.net_io_counters()
            print(
                f"Bytes Sent: {network_io.bytes_sent} bytes and the Packets Sent: {network_io.packets_sent}"
            )
            print(
                f"Bytes Received: {network_io.bytes_recv} bytes and the Packets Recv: {network_io.packets_recv}"
            )
            time.sleep(1)

    @classmethod
    async def monitor_system(cls, duration):
        tasks = [
            monitor_io(cls.process_id, duration),
            monitor_memory(cls.process_id, duration),
            monitor_cpu(cls.process_id, duration),
        ]

        await asyncio.gather(*tasks)

    def monitor_process(self, process_name):
        with open(
            f"process_monitor_{self.process_name}_{self.process_id}.csv", "a+"
        ) as f:
            f.write(f"DateTime, CPU%, Memory%\n")
            while True:
                current_time = datetime.datetime.now(datetime.UTC).strftime(
                    "%Y年%m月%d日 %H时%M分%S秒 %f微秒"
                )
                cpu_percent = psutil.Process(self.process_id).cpu_percent(interval=0.5)
                memory_percent = psutil.Process(self.process_id).memory_percent()
                line_info = (
                    f"{current_time}, {str(cpu_percent)}, {str(memory_percent)}\n"
                )
                f.write(line_info)
                time.sleep(self.interval_epoch)


# ---------------------------
if __name__ == "__main__":
    pass
