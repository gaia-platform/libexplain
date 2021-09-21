Fork of libexplain meant to be maintained by Gaia.

This fork is based off the Debian patches. At time of writing these are all the Debian patches applied: https://sources.debian.org/patches/libexplain/1.4.D001-11/


```bash
CPPFLAGS='-fPIC' ./configure --prefix=/usr
make -j$(nproc)
make install
```
