#!/usr/bin/make -f

PAPER = paper
TEX = $(wildcard *.tex body/*.tex)
BIB = reference/paper.bib
FIGS = $(wildcard figs/*.pdf figs/*.png)

.PHONY: all clean open

$(PAPER).pdf: $(TEX) $(BIB) $(FIGS) formatting/jpaper.cls
	echo $(FIGS)
	pdflatex $(PAPER)
	bibtex $(PAPER)
	pdflatex $(PAPER)
	pdflatex $(PAPER)
	rm -f *.aux *.bbl *.blg *.log *.out

clean:
	rm -f *.aux *.bbl *.blg *.log *.out $(PAPER).pdf

open:
	open $(PAPER).pdf
