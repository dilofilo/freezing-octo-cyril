# Usage:
# make          # make dvi, ps, and pdf
# make dvi      # make dvi
# make ps       # make ps (and dvi)
# make pdf      # make pdf
#

MAIN		= designdoc
SOURCES	= $(wildcard ./*.tex)
EPSFIGURES	= $(patsubst %.fig,%.eps,$(wildcard ./images/*.fig))
PDFFIGURES	= $(patsubst %.fig,%.pdf,$(wildcard ./images/*.fig))

all: 
	pdflatex designdoc.tex
clean:
	rm -f *.pdf
	rm -f *.log
	rm -f *.aux
	rm -f *.out
#dvi: ${MAIN}.dvi
#pdf: ${MAIN}.pdf
#ps: ${MAIN}.ps

#${MAIN}.dvi : ${SOURCES} ${EPSFIGURES}
#	latex ${MAIN}
#	@while ( grep "Rerun to get cross-references"	\
#		${MAIN}.log > /dev/null ); do		\
#		echo '** Re-running LaTeX **';		\
#		latex ${MAIN};				\
#		done

#${MAIN}.pdf : ${SOURCES} ${PDFFIGURES}
#	pdflatex ${MAIN}
#	@while ( grep "Rerun to get cross-references" 	\
#		${MAIN}.log > /dev/null ); do		\
#		echo '** Re-running LaTeX **';		\
#		pdflatex ${MAIN};				\
#	done
#
#${MAIN}.ps : ${MAIN}.dvi
 #       # running dvips
#	dvips ${MAIN}.dvi -o ${MAIN}.ps
#clean:
#	rm -f ./images/*.tex
#	rm -f ./images/*.eps
#	rm -f ./images/*.pdf
#	rm -f ./images/*.bak
#	rm -f ./*.aux
#	rm -f ./*.tex~
#
# (re)Make .eps is .fig if newer
#
#%.eps : %.fig
 #       #Creates .eps file
#	fig2dev -L pstex $*.fig > $*.eps
 #       #Creates .tex file
#	fig2dev -L pstex_t -p $* $*.fig > $*.tex
#
# (re)Make .pdf if .esp is newer
#
#%.pdf : %.eps
	#Creates .pdf files from .esp files
#	epstopdf $*.eps > $*.pdf