SUBDIRS = monitor meteo

all: subs

subs:
	for dir in $(SUBDIRS) ; do make -C $$dir ; done

clean:
	for dir in $(SUBDIRS) ; do make clean -C $$dir ; done
