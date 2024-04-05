import os
import cv2
import numpy as np
from PIL import Image
from tqdm import tqdm
from torch.utils.data import Dataset
import torch


def get_mean_and_std(dataset, batch_size=128, num_workers=2):
    """Compute the mean and std value of dataset.
    transform = transforms.Compose([transforms.ToTensor()]) must be used in dataset.
    data: shape = (N,C,W,H)
    """
    device = torch.device("cuda" if torch.cuda.is_available() else "cpu")
    loader = torch.utils.data.DataLoader(
        dataset, batch_size=batch_size, num_workers=num_workers
    )
    bt_mean = []
    bt_std = []
    for inputs, _ in tqdm(loader, desc="compute mean and std"):
        inputs = inputs.to(device)
        bt_mean.append(inputs.mean(dim=(-2, -1)))
        bt_std.append(inputs.std(dim=(-2, -1)))

    mean = torch.cat(bt_mean).mean(dim=0)
    std = torch.cat(bt_std).mean(dim=0)

    return mean, std


def compute_mean_std(dataset):
    """输入 PyTorch 的 Dataset, 输出均值和标准差."""
    mean_r, mean_g, mean_b = 0.0, 0.0, 0.0
    for img, _ in dataset:
        img = np.asarray(img)  # change PIL Image to numpy array
        mean_r += np.mean(img[:, :, 0])
        mean_g += np.mean(img[:, :, 1])
        mean_b += np.mean(img[:, :, 2])

    mean_r /= len(dataset)
    mean_g /= len(dataset)
    mean_b /= len(dataset)

    diff_r, diff_g, diff_b = 0.0, 0.0, 0.0
    N = 0
    for img, _ in dataset:
        img = np.asarray(img)
        diff_r += np.sum(np.power(img[:, :, 0] - mean_r, 2))
        diff_g += np.sum(np.power(img[:, :, 1] - mean_g, 2))
        diff_b += np.sum(np.power(img[:, :, 2] - mean_b, 2))

        N += np.prod(img[:, :, 0].shape)

    std_r = np.sqrt(diff_r / N)
    std_g = np.sqrt(diff_g / N)
    std_b = np.sqrt(diff_b / N)

    mean = (mean_r.item() / 255.0, mean_g.item() / 255.0, mean_b.item() / 255.0)
    std = (std_r.item() / 255.0, std_g.item() / 255.0, std_b.item() / 255.0)

    return mean, std
