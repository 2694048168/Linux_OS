#!/usr/bin/env python3
# -*- coding: utf-8 -*-

"""
@File: image_downsample.py
@Python Version: 3.12.1
@Platform: PyTorch 2.0.0+cu118
@Author: Wei Li or Ithaca (weili_yzzcq@163.com)
@Date: 2024-04-05
@Version: 0.1.1
@copyright Copyright (c) 2023 Wei Li
@arXiv: 
@Brief:  
@Description: 
"""

import os
import glob
import tqdm
import cv2


def image_downsampling(origin_folder, save_folder, scale=4, interpolation="area"):
    image_list = []
    for extension in ["png", "jpg", "jpeg", "bmp", "tiff", "gif", "webp"]:
        image_list += glob.glob(os.path.join(origin_folder, f"**/*.{extension}"))
    assert len(image_list), f"there is not any image in the {origin_folder}!"

    for file in tqdm.tqdm(image_list):
        img = cv2.imread(file, flags=cv2.IMREAD_UNCHANGED)  # BGR or BGRA
        height, width, channels = img.shape
        if min(height, width) >= 2160:  # the 4K spatial resolution
            img = cv2.GaussianBlur(img, ksize=(13, 13), sigmaX=0)
        img = cv2.resize(img, (width // scale, height // scale), cv2.INTER_AREA)
        basename = os.path.basename(file)
        cv2.imwrite(os.path.join(save_folder, basename), img)
        print(f"--->finished downsampling processing for the image {basename}.")
    print(
        f"--->finished downsampling processing for all image in {origin_folder} and saving into {save_folder}!"
    )


# -------------------------
if __name__ == "__main__":
    origin_folder = ""
    save_folder = "./image_downsamples"
    os.makedirs(save_folder, exist_ok=True)

    image_downsampling(origin_folder, save_folder)
