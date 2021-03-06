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

## Make:  [Top (GNU make)](https://www.gnu.org/software/make/manual/html_node/)

especially: [Automatic Variables (GNU make)](https://www.gnu.org/software/make/manual/html_node/Automatic-Variables.html#Automatic-Variables)

TLDR:

[Makefile Tutorial By Example](https://makefiletutorial.com/)

> There's a nice [list of options](http://www.gnu.org/software/make/manual/make.html#Options-Summary) that can be run from make. Check out `--dry-run`, `--touch`, `--old-file`.
>
> You can have multiple targets to make, i.e. `make clean run test` runs the `clean` goal, then `run`, and then `test`.

[A Simple Makefile Tutorial (colby.edu)](https://www.cs.colby.edu/maxwell/courses/tutorials/maketutor/)

<mark>Note that order of entries in Makefile matters - it begins the first rule by default, then the rest is dependencies oriented. That said, if some latter targets are not dependencies of previous rules, they might not be executed </mark>

Some mistake I made: [`<mark>`c - How do I make Makefile to recompile only changed files? - Stack Overflow `</mark>`](https://stackoverflow.com/questions/7815400/how-do-i-make-makefile-to-recompile-only-changed-files)

In short, makefile treat target name as file name.

If no target files exist: it will recompile it.

If target files exist: it won't recompile it.

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

## Github workflows - GitHub Pages

Compare common stacks that are known to be good for rendering static websites.

### Mkdocs

Mkdocs has some issues: [Navigation not in alphanumeric order (when pages config is automatic) · Issue #638 · mkdocs/mkdocs (github.com)](https://github.com/mkdocs/mkdocs/issues/638) that can be solved through:

[lukasgeiter/mkdocs-awesome-pages-plugin: An MkDocs plugin that simplifies configuring page titles and their order](https://github.com/lukasgeiter/mkdocs-awesome-pages-plugin)

[courses/update_navigation_order.sh](https://github.com/luchaoqi/courses/blob/1bd2d8c0990b9bd21d5d10ac144554ad5750c976/update_navigation_order.sh)

**Anyways, it orders pages based on lexicographical order by default. This saves a lot of time compared to manually generating or writing specific indexing file in order to maintain the navigation bar.**

### Jekyll

Jekyll provides the most beautiful UI/themes from what I can tell - but its navigation bar needs to be manually maintained/hard-coded. To get something in quickly:
[stanford-cs329s/reports: Final reports for CS 329S Winter 2021](https://github.com/stanford-cs329s/reports)

Based on Jekyll, I love `Just the Docs`, which also requires hard-coding the navigation bar, but it's a lot ?convenient using in-page `YAML front matter` [Navigation Structure | Just the Docs](https://just-the-docs.github.io/just-the-docs/docs/navigation-structure/)

[rnnh/bioinfo-notebook: 🔬 Bioinformatics Notebook. Scripts for bioinformatics pipelines, with quick start guides for programs and video demonstrations.](https://github.com/rnnh/bioinfo-notebook)

### Docsify

Docsify is installed through `npm` which is not installed in the server that I am currently using - don't want to install it on a industry server without `sudo`
Also, it need to hard-code navigation bar like `jekyll` using [docsify/_sidebar.md at master · docsifyjs/docsify](https://github.com/docsifyjs/docsify/blob/master/docs/_sidebar.md)
### [Read the Docs](https://readthedocs.org/)

It needs to hard-code navigation bar using `index.rst`: [marcelm/cutadapt: Cutadapt removes adapter sequences from sequencing reads](https://github.com/marcelm/cutadapt)

Like [Sphinx Tutorial — Sphinx Tutorial 1.0 documentation](https://sphinx-tutorial.readthedocs.io/#), the main advantage is that it provides version controls - really easy to check old versions of the docs.


Overall, I personally prefer to [just-the-docs/just-the-docs: A modern, high customizable, responsive Jekyll theme for documention with built-in search.](https://github.com/just-the-docs/just-the-docs), but I am not sure if it is the best choice.
