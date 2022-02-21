## Takeaways

```bash
cat /usr/share/dict/words | grep ".*a.*a.*a" | grep -v "'s$" | sed -E "s/.*(..)/\1/" | sort | uniq -c | sort -n | tail -n3 | awk '{print $2}'

cat /usr/share/dict/words | grep ".*a.*a.*a" | grep -v "'s$" | sed -E "s/.*(..)/\1/" | sort | uniq | wc -l
```

```bash
# missing combinations
cat /usr/share/dict/words | grep ".*a.*a.*a" | grep -v "'s$" | sed -E "s/.*(..)/\1/" | sort | uniq > com_seen
source com_all.sh > com_all
comm -3 com_all com_seen > com_missing
```
