#!/usr/bin/env python3
# -*- coding: utf-8 -*-

"""
@File: lib_var.py
@Python Version: 3.12.1
@Platform: PyTorch 2.0.0 + cu117
@Author: Wei Li (Ithaca)
@Date: 2024-08-07.
@Contact: weili_yzzcq@163.com
@Blog: https://2694048168.github.io/blog/#/
@Version: V2.1
@License: Apache License Version 2.0, January 2004
    Copyright 2024. All rights reserved.

@Description: 
"""

# # script.bat
# @echo off
# dir /b *.lib > lib_files.txt
# echo "All *.lib filename haves been written into lib_files.txt"

import os
import glob


def getVTKLibVariable(originalFolder, saveFolder, saveFilename):
    lib_list = []
    lib_list += glob.glob(os.path.join(originalFolder, f"*.lib"))
    assert len(lib_list), f"there is not any lib file int the {originalFolder}"

    var_lib = str()
    for idx, filename in enumerate(lib_list):
        file = filename.split("\\", -1)[-1] + ";"
        var_lib += file

    save_path = saveFolder + saveFilename
    with open(save_path, "w") as f:
        f.write(var_lib)
    print(f"there VTK lib_variable into {save_path}")


if __name__ == "__main__":
    original_folder = R"D:\download\VTK-9.3.1\install\lib/"
    save_folder = R"D:\download\VTK-9.3.1\install\lib/"
    filename = "lib_var.txt"
    os.makedirs(save_folder, exist_ok=True)

    getVTKLibVariable(original_folder, save_folder, filename)
