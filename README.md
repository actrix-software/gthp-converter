# gthp-converter

Formats a GIF to an array of PNGs declared in a C++ header file. 

Since there is no support for GIFs in d3d9, it shows an easy way to use them.

Below is an example how you could use the created header file.


# Usage of the binary

Step 1: Goto https://cloudconvert.com/gif-to-png (not associated).

Step 2: Upload your GIF select convert to PNG, convert it and download the zip.

Step 3: Unzip the files into a empty folder.

Step 4: Drag and drop "yourfile-1.png" over gthp-converter.exe.

Step 5: In the directory of your gthp-converter should be a new file called "yourfile.hpp".


# Example usage of the header file

```cpp

std::vector<void*> LoadImages(LPDIRECT3DDEVICE9 pDevice, std::vector<std::pair<unsigned char*, int>>& ImageData) {

  std::vector<void*> Images;
  
  for (int i = 0; i < ImageData.size(); i++) {
  
    PDIRECT3DTEXTURE9 Image;
  
    auto Result = D3DXCreateTextureFromFileInMemory(pDevice, ImageData[i].first, ImageData[i].second, &Image);
  
    if (Result != S_OK) {
  
      continue;
    }
    
    Images.push_back(Image);
  }
}
```


# Warnings

If your GIF has to many frames, there is a very high chance that your run out of memory quickly! ;)
