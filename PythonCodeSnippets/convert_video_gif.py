#!/usr/bin/env python3
# -*- coding: utf-8 -*-

"""
@File: convert_video_gif.py
@Python Version: 3.12.1
@Platform: PyTorch 2.0.0 + cu117
@Author: Wei Li (Ithaca)
@Date: 2024-06-22.
@Contact: weili_yzzcq@163.com
@Blog: https://2694048168.github.io/blog/#/
@Version: V2.1
@License: Apache License Version 2.0, January 2004
    Copyright 2024. All rights reserved.

@Description: 
"""

import glob

import cv2
from PIL import Image


def convert_mp4_jpg(input_file):
    # 先将mp4文件的所有帧读取出保存为图片
    video_capture = cv2.VideoCapture(input_file)
    still_reading, image = video_capture.read()
    frame_count = 0
    while still_reading:
        cv2.imwrite(f"output/frame_{frame_count:03d}.jpg", image)
        # read next image
        still_reading, image = video_capture.read()
        frame_count += 1


def convert_images_gif(output_file):
    # 读取目录下图片，用Pillow模块的Image和所有图片合并
    # 成一张gif
    images = glob.glob(f"output/*.jpg")
    images.sort()
    frames = [Image.open(image) for image in images]
    frame_one = frames[0]
    frame_one.save(
        output_file,
        format="GIF",
        append_images=frames[1:],
        save_all=True,
        duration=40,
        loop=0,
    )


def convert_mp4_gif(input_file, output_file):
    convert_mp4_jpg(input_file)
    convert_images_gif(output_file)


# frame_one.save(output_file, format="GIF",
# append_images=[f for i, f in enumerate(frames[1:]) if i % 2 == 0],
#    save_all=True, duration=40, loop=0)


def mp4_to_gif2():
    clip = VideoFileClip("demo.mp4")
    clip.write_gif("output2.gif")


def convert_gif_to_mp4():
    import moviepy.editor as mp

    clip = mp.VideoFileClip("demo.gif")
    clip.write_videofile("output.mp4")


# ==========================
if __name__ == "__main__":
    filepath = R"C:\Users\26940\Desktop\Recording 2024-06-22 123005.mp4"
    save_filename = "./output.gif"

    convert_mp4_gif(filepath, save_filename)
