## Takeaways

```sh
ll
mkdir missing
cd missing/
touch semester
echo '#!/bin/sh' | tee semester
echo 'curl --head --silent https://missing.csail.mit.edu' | tee -a semester
chmod +x semester
./semester
touch last-modified.txt | date -r semester > last-modified.txt
cat last-modified.txt
cat /sys/class/thermal/thermal_zone*/temp
history | tail -n 20
```
