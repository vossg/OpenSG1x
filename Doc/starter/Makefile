# Makefile for starter guide
# mainly needed to convert the pictures from whatever to eps
# and then call lyx to make the guide

MAINDOC = starter.ps

FIGS = 	$(wildcard *.fig) 
GIFS = 	$(wildcard *.gif) 
JPGS = 	$(wildcard *.jpg) 
TIFS = 	$(wildcard *.tif) 
GPLS = 	$(wildcard *.gpl) 
EPSS = 	$(wildcard *.eps.gz) 

PS = 	$(patsubst %.fig,%.eps,${FIGS})	\
	$(patsubst %.gif,%.eps,${GIFS})	\
	$(patsubst %.jpg,%.eps,${JPGS})	\
	$(patsubst %.tif,%.eps,${TIFS})	\
	$(patsubst %.gpl,%.eps,${GPLS}) \
	$(patsubst %.eps.gz,%.eps,${EPSS})

# Targets

.PHONY: clean Clean

default: ${PS} ${MAINDOC}

clean:
	rm -f ${PS}

Clean: clean
	rm -f ${MAINDOC}

# conversion rules	

%.ps: %.lyx
	lyx -e ps $<

%.eps: %.gif
	convert $< PS2:$@ 

%.eps: %.tif
	convert $< PS2:$@ 

%.eps: %.jpg
	jpeg2ps -q $< > $@ 

%.eps: %.fig
	fig2dev -L ps $< $@ 

%.eps: %.gpl
	gnuplot $<

%.eps: %.ps
	cp $< $@ 
	touch $@

%.eps: %.eps.gz
	gzip -dc $< > $@ 
	touch $@
