#!/usr/bin/env python3
import os
import sys
from PIL import Image  # Requires Pillow library

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
        print(extrema)
        if extrema[3][0] < 255:
            return True
    return False

def main():
    os.makedirs("transparent_pngs", exist_ok=True)
    moved = 0
    
    for filename in os.listdir("."):
        if not filename.lower().endswith(".png"):
            continue
        
        try:
            with Image.open(filename) as img:
                if has_transparency(img):
                    os.rename(filename, f"transparent_pngs/{filename}")
                    print(f"✓ {filename} (has transparency)")
                    moved += 1
                else:
                    print(f"✗ {filename} (opaque)")
        except Exception as e:
            print(f"! {filename} (error: {str(e)})")
    
    print(f"\nDone. Moved {moved} files to 'transparent_pngs/'")

if __name__ == "__main__":
    main()