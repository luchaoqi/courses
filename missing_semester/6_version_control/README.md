# Takeaways

[Git 101](https://luchaoqi.com/blog/Git-101/)

# Exercices

```zsh
# zsh using git plugin
# play around with all git aliases
# e.g.
alias | grep  'git log'

# visualize log
glog

# check history of certain file
glg README.md
# glgg
# glgga

# commit associated with a certain content in a file
gbl README.md
# search for the content e.g. `jobs` like in the vi/vim editor
/jobs
# get the hash for the commit e.g. f0931819
gsh f0931819

# remove large/sensitive data
git filter-branch --force --index-filter \
"git rm --cached --ignore-unmatch PATH-TO-YOUR-FILE-WITH-SENSITIVE-DATA" \
--prune-empty --tag-name-filter cat -- --all

# git stash performs like a stack
# it pushes changes (no untracked files by default otherwise add -u including untracked files) to a stack (dirty working dir)
# and git stash pop (gstp) to turn changes back

```
