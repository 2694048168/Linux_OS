import os
import glob

# -------------------------
if __name__ == "__main__":
    origin_folder = ""
    image_list = []
    for extension in ["png", "jpg", "jpeg", "bmp", "tiff", "gif", "webp"]:
        image_list += glob.glob(os.path.join(origin_folder, f"*.{extension}"))
    assert len(image_list), f"there is not any image in the {origin_folder}!"
