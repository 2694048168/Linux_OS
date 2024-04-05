# set the visible GPU devices via Command Line
# $: CUDA_VISIBLE_DEVICES=0,1 python train.py

# set the environ variable in source code in python file
import os
import torch

os.environ["CUDA_VISIBLE_DEVICES"] = "0,1"

device = torch.device(f"cuda:{gpu_id}" if torch.cuda.is_available() else "cpu")
