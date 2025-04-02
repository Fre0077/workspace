#!/bin/bash

mkdir -p transparent_pngs

for file in *.png; do
  if [[ -f "$file" ]]; then
    echo "Checking: $file"
    if file "$file" | grep -q "RGBA"; then
      echo "  ↳ Transparency detected! Moving..."
      mv "$file" transparent_pngs/
    else
      echo "  ↳ No transparency."
    fi
  fi
done

echo "Done! Files moved to: transparent_pngs/"