[The Missing Semester of Your CS Education · the missing semester of your cs education (mit.edu)](https://missing.csail.mit.edu/)

Most of manuals of software used in the lecture can be found here:

[Software - GNU Project - Free Software Foundation](https://www.gnu.org/software/software.html)

e.g.

[Automatic Variables (GNU make)](https://www.gnu.org/software/make/manual/html_node/Automatic-Variables.html#Automatic-Variables)

Resources:

[计算机教育中缺失的一课 · the missing semester of your cs education (missing-semester-cn.github.io)](https://missing-semester-cn.github.io/)

[2019 Lectures · the missing semester of your cs education (mit.edu)](https://missing.csail.mit.edu/2019/)

[Ivan-Kim/MIT-missing-semester: Complete solutions for 2020 MIT Missing Semester course](https://github.com/Ivan-Kim/MIT-missing-semester)

```bash
for file in *; do mv "$file" `echo $file | tr ' ' '_'` ; done
for file in [0-9]; do mv "$file" "exercise_$file"; done;
for file in exercise_*; do mv "$file" "${file#exercise_}"; done;
```
