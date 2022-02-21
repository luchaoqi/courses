## Version controls for dependencies

> Take a look at the various ways to specify version requirements for dependencies in [Rust’s build system](https://doc.rust-lang.org/cargo/reference/specifying-dependencies.html). Most package repositories support similar syntax. For each one (caret, tilde, wildcard, comparison, and multiple), try to come up with a use-case in which that particular kind of requirement makes sense.

`major.minor.patch` Release increments number of:

- *patch*: API hasn’t changed
- *minor*: API has new, backwards-compatible changes
- *major*: API has backwards-incompatible change

[Specifying Dependencies - The Cargo Book (rust-lang.org)](https://doc.rust-lang.org/cargo/reference/specifying-dependencies.html)

```bash
# Caret requirements
# An update is allowed if the new version number does not modify the left-most non-zero digit in the major, minor, patch grouping.
^1.2.3  :=  >=1.2.3, <2.0.0
^1.2    :=  >=1.2.0, <2.0.0
^1      :=  >=1.0.0, <2.0.0
^0.2.3  :=  >=0.2.3, <0.3.0
^0.2    :=  >=0.2.0, <0.3.0
^0.0.3  :=  >=0.0.3, <0.0.4
^0.0    :=  >=0.0.0, <0.1.0
^0      :=  >=0.0.0, <1.0.0

# Tilde requirements
# If you specify a major, minor, and patch version or only a major and minor version, only patch-level changes are allowed. If you only specify a major version, then minor- and patch-level changes are allowed.
~1.2.3  := >=1.2.3, <1.3.0
~1.2    := >=1.2.0, <1.3.0
~1      := >=1.0.0, <2.0.0

# Wildcard requirements
*     := >=0.0.0
1.*   := >=1.0.0, <2.0.0
1.2.* := >=1.2.0, <1.3.0
```

## Make

manual: [Top (GNU make)](https://www.gnu.org/software/make/manual/html_node/)

especially: [Automatic Variables (GNU make)](https://www.gnu.org/software/make/manual/html_node/Automatic-Variables.html#Automatic-Variables)

TLDR:

[Makefile Tutorial By Example](https://makefiletutorial.com/)

> ## Arguments to make
>
> There's a nice [list of options](http://www.gnu.org/software/make/manual/make.html#Options-Summary) that can be run from make. Check out `--dry-run`, `--touch`, `--old-file`.
>
> You can have multiple targets to make, i.e. `make clean run test` runs the `clean` goal, then `run`, and then `test`.

[A Simple Makefile Tutorial (colby.edu)](https://www.cs.colby.edu/maxwell/courses/tutorials/maketutor/)

`Makefile`

`<mark>` Note that order of entries in Makefile matters `</mark>`

```makefile
paper.pdf: paper.tex plot-data.png
	pdflatex paper.tex

plot-%.png: %.dat plot.py
	./plot.py -i $*.dat -o $@

.PHONY: clean
# clean is a phony target that is not a file named clean.
clean:
	git ls-files -o | xargs rm -f
```

similar command from [pre-commit](https://pre-commit.com/index.html#cli)

`git ls-files -- '*.py' | xargs pre-commit run --files`: run all hooks against all `*.py` files in the repository.

`.git/hooks/pre-commit`

```bash
#!/bin/sh
# https://jsinkers.github.io/notes/notebooks/missing_class/08_metaprogramming.html
# Pre-commit script to prevent commit if the make fails
# Redirect output to stderr.

exec 1>&2

if make

then
	echo "Make successful"
else
	cat << EOF
	Error: could not make pdf
	EOF
	exit 1
fi

# OR run spefic command only, in this case paper.pdf entry only

#!/bin/sh
if ! make paper.pdf ; then
    echo "Cannot make paper.pdf"
    exit 1
fi
```

## Github workflows - No Jekyll

For the sake of life, no Jekyll which is not newbie friendly.

Use other alternatives like MkDocs etc.