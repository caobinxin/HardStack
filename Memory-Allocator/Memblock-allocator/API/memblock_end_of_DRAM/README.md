memblock_end_of_DRAM [中文教程](https://biscuitos.github.io/blog/MMU-ARM32-MEMBLOCK-memblock_information/)
--------------------------------------------

* function: Find a valid memory from special area.


## Usage

* patch file

```
git am *.patch kernel_src/
```

* driver file

```
Device Driver--->
    [*]BiscuitOS Driver--->
        [*]Memblock allocator
            [*]memblock_end_of_DRAM()
```
