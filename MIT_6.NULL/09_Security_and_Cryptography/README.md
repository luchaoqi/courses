## Exercises

1. Entropy

   1. four concatenations: log2(10^20)≈66.4
   2. 62 possibilities > log2(62^8)≈47.6
   3. previous one with larger entropy
   4. 3*10^8 years and 692 years
2. ```bash
   % sha256sum debian-mac-11.2.0-amd64-netinst.iso | shasum --algorithm 256 --check
   debian-mac-11.2.0-amd64-netinst.iso: OK
   ```
3. ```bash
   $ openssl aes-256-cbc -salt -in secret.txt -out secret.enc.txt
   enter aes-256-cbc encryption password:
   Verifying - enter aes-256-cbc encryption password:
   $ openssl aes-256-cbc -d -in secret.enc.txt -out secret.dec.txt
   enter aes-256-cbc decryption password:
   $ cmp secret.txt secret.dec.txt | echo $?
   0
   ```
