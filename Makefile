SUBDIRS = EzClient EzServer

.PHONY: $(SUBDIRS) all clean

all: $(SUBDIRS)

$(SUBDIRS):
	$(MAKE) -C $@

clean:
	-for d in $(SUBDIRS); do (cd $$d; $(MAKE) clean ); done
