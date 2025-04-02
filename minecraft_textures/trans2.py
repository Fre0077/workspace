#!/usr/bin/env python3
import os
import sys
from PIL import Image

def has_transparency(img):
    if img.info.get("transparency", None) is not None:
        return True
    if img.mode == "P":
        transparent = img.info.get("transparency", -1)
        for _, index in img.getcolors():
            if index == transparent:
                return True
    elif img.mode == "RGBA":
        extrema = img.getextrema()
        if extrema[3][0] < 255:
            return True
    return False

def is_rectangular(img):
    return img.size[0] == img.size[1]  # Width == Height

def is_128x128(img):
    return img.size == (128, 128)

def main():
    # Create target folders
    os.makedirs("transparent_pngs", exist_ok=True)
    os.makedirs("non_rectangular", exist_ok=True)
    os.makedirs("wrong_res", exist_ok=True)
    
    moved_transparent = 0
    moved_non_rect = 0
    moved_wrong_res = 0
    
    for filename in os.listdir("."):
        if not filename.lower().endswith(".png"):
            continue
        
        try:
            with Image.open(filename) as img:
                # Check rectangular
                if not is_rectangular(img):
                    os.rename(filename, f"non_rectangular/{filename}")
                    print(f"⬜ {filename} (non-rectangular)")
                    moved_non_rect += 1
                    continue
                
                # Check resolution first (fastest check)
                if not is_128x128(img):
                    os.rename(filename, f"wrong_res/{filename}")
                    print(f"⚠ {filename} (wrong resolution)")
                    moved_wrong_res += 1
                    continue
                
                # Check transparency last (slowest check)
                if has_transparency(img):
                    os.rename(filename, f"transparent_pngs/{filename}")
                    print(f"✓ {filename} (transparent)")
                    moved_transparent += 1
                else:
                    print(f"✗ {filename} (valid)")
                    
        except Exception as e:
            print(f"! {filename} (error: {str(e)})")
    
    print(f"\nResults:")
    print(f"- Moved {moved_transparent} transparent PNGs to 'transparent_pngs/'")
    print(f"- Moved {moved_non_rect} non-rectangular images to 'non_rectangular/'")
    print(f"- Moved {moved_wrong_res} wrong-resolution images to 'wrong_res/'")

if __name__ == "__main__":
    main()