# antSSL

包括了对称加密（aes128和aes256）哈希函数（SHA224，256，384，512）和消息认证码（HMAC-SHA-224，256，384，512）

#### Dependencies

- GMP Library:

  `$ sudo apt-get install libgmp3-dev`

- OpenSSL:

  `$ sudo apt-get install libssl-dev`

- [PBC Library](https://crypto.stanford.edu/pbc)

  ```
  $ ./configure --prefix=$HOME/.local
  $ make
  $ make install
  ```

  Makefile uses this path. In case of change in destination directory, update the Makefile accordingly.

#### Build

```
$ make
```