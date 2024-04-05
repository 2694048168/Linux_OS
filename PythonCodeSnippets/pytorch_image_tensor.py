import torch
import torchvision
import PIL
from PIL import Image
import numpy
import numpy as np


# -------------------------
if __name__ == "__main__":
    # Step 1. torch.Tensor -> PIL.Image.
    image = PIL.Image.fromarray(
        torch.clamp(tensor * 255, min=0, max=255).byte().permute(1, 2, 0).cpu().numpy()
    )
    # Equivalently way as follow
    image = torchvision.transforms.functional.to_pil_image(tensor)

    # Step 2. PIL.Image -> torch.Tensor.
    tensor = (
        torch.from_numpy(np.asarray(PIL.Image.open(filepath))).permute(2, 0, 1).float()
        / 255
    )
    # Equivalently way as follow
    tensor = torchvision.transforms.functional.to_tensor(PIL.Image.open(filepath))

    # Step 3. np.ndarray -> PIL.Image.
    image = PIL.Image.fromarray(ndarray.astypde(np.uint8))

    # Step 4. PIL.Image -> np.ndarray.
    ndarray = np.asarray(PIL.Image.open(filepath))
