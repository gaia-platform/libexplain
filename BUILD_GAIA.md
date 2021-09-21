Fork of libexplain meant to be maintained by Gaia.

This fork is based off the Debian patches. At time of writing these are all the Debian patches applied: https://sources.debian.org/patches/libexplain/1.4.D001-11/. As Debian keeps publishing patches we should apply them to this fork.


```bash
# Even though clang is used to compile gcc is used to link and it 
# won't recognize '-fuse-ld=lld-10'
unset LDFLAGS 
CPPFLAGS='-fPIC' ./configure --prefix=/usr
make -j$(nproc)
make install
```
