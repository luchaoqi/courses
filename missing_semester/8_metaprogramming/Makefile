paper.pdf: paper.tex plot-data.png
	pdflatex paper.tex

plot-%.png: %.dat plot.py
	./plot.py -i $*.dat -o $@

.PHONY: clean
# clean is a phony target that is not a file named clean.
clean:
	git ls-files -o | xargs rm -f