![r3engine](r3engine/assets/r3-sticker.png)

![GitHub Stars](https://img.shields.io/github/stars/r3shape/r3engine?style=for-the-badge&label=stars&labelColor=black&color=white)
![License](https://img.shields.io/badge/mit-badge?style=for-the-badge&logo=mit&logoColor=white&label=License&labelColor=black&color=white)

---

### Relevant Links

| [Module Reference](https://github.com/r3shape/r3engine/blob/main/docs/module_ref/module_ref.md) | [API Reference](https://github.com/r3shape/r3engine/blob/main/docs/api_ref/api_ref.md) | [Example Guides](https://github.com/r3shape/r3engine/blob/main/docs/examples/examples.md) |  [Example Code](https://github.com/r3shape/r3engine/tree/main/examples) |   
| [Official Discord](https://discord.gg/kreGBCVsQQ) | [Official Reddit](https://www.reddit.com/r/r3engineEngine/) | [r3engine Discussions](https://github.com/r3shape/r3engine/discussions) | [r3engine FAQ](https://github.com/r3shape/r3engine/wiki/r3engine-FAQ) |  


## Building the Engine Source

> **NOTE**: If you're using the `r3make` CLI tool, ensure **Python** is installed. For more information, check out the [r3make Repository](https://github.com/r3shape/r3make).

r3engine includes **pre-configured `.r3make` files** for easy setup and compilation. **[r3make](https://github.com/r3shape/r3make)** is the recommended tool for fast, simple, efficient builds.

---

### Option 1: Build with **r3make** (Recommended)

1. **Install r3make**:  
   Install via **PyPI**:  
   ```bash
   pip install r3make
   ```

2. **Clone the Repository**:  
   ```bash
   git clone https://github.com/r3shape/r3engine
   cd r3engine
   ```

3. **Build the Engine**:  
   ```bash
   r3make scripts/r3engine.r3make
   ```

4. **Output**:  
   The compiled `r3engine.dll` will be located in the `build` directory.

---

### Option 2: Manual Compilation

For those who wish to **wield the source** themselves:

1. **Clone the Repository**:  
   ```bash
   git clone https://github.com/r3shape/r3engine
   cd r3engine
   ```

2. **Compile the Engine**:  
   Manually compile using **GCC**:  
   ```bash
   gcc -c r3engine/modules/core/src/*.c -Ir3engine/include -DLOTUS_DLL_EXPORT -o build/*.o
   gcc -shared build/*.o -lopengl32 -lgdi32 -o build/r3engine.dll
   ```

3. **Install Compiled Binaries**:  
   ```bash
   cp build/r3engine.dll your_project/bin/
   ```

<br>

## Building Projects with **r3engine**

1. **Prepare Your Project**:  
   Set up your source files, including necessary paths.

2. **Compile with r3make or GCC**:  
   Example using **GCC**:  
   ```bash
   gcc my_project.c -Ir3engine/include -lr3engine -o my_project.exe
   ```

<br>

## r3engine Contributors

<a href="https://github.com/r3shape/r3engine/graphs/contributors">
  <img src="https://contrib.rocks/image?repo=r3shape/r3engine&max=500&columns=20&anon=1" />
</a>

<br>

## License

r3engine is licensed under the **MIT License**.
