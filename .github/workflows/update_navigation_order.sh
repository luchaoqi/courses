#!/usr/bin/env bash
# add .pages for certain folders
set -e
# go through folders
for folder in $(ls -d */); do
    # if this folder contains files that start with two or more digits
    if [[ $(ls "$folder" | grep -E '^[0-9]{2,}') ]]; then
        # add .pages to the folder name
        echo "Add .pages to $folder for mkdocs-awesome-pages-plugin"
        echo -e "nav:\n- ...\n$(ls -1 "$folder" | grep -E '([0-9]{2,})' | sed 's/^/- /')" > "$folder"/.pages
        continue # go to next folder
    fi
done
