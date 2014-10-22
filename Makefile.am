CC = g++
CPP = g++
CXX = g++

SDL_CFLAGS = `sdl-config --cflags`
SDL_LDFLAGS = `sdl-config --libs`

WX_CFLAGS = `wx-config --version=2.8 --cflags`
WX_LDFLAGS = `wx-config --version=2.8 --libs`

ACLOCAL_AMFLAGS = -I m4

SUBDIRS = src

EXTRA_DIST=rom autogen.sh Doxyfile.in README.md logo.png logo.svg keymap.cfg contrib

CLEANFILES = caprice32wx.conf *~

etcdir = $(sysconfdir)/@PACKAGE@
etc_DATA = caprice32wx.conf keymap.cfg

do_subst = sed -e 's,[@]sharedstatedir[@],$(sharedstatedir),g' \
		-e 's,[@]localstatedir[@],$(localstatedir),g' \
		-e 's,[@]sysconfdir[@],$(sysconfdir),g' \
		-e 's,[@]prefix[@],$(prefix),g' \
		-e 's,[@]bindir[@],$(bindir),g' \
		-e 's,[@]mandir[@],$(mandir),g' \
		-e 's,[@]PERL[@],$(PERL),g' \
		-e 's,[@]CC[@],$(CC),g' \
		-e 's,[@]CXX[@],$(CXX),g' \
		-e 's,[@]PACKAGE[@],$(PACKAGE),g' \
		-e 's,[@]VERSION[@],$(VERSION),g'

caprice32wx.conf: caprice32wx.conf.in Makefile
	$(do_subst) < $(srcdir)/caprice32wx.conf.in > caprice32wx.conf

docdir = $(datarootdir)/doc/@PACKAGE@
doc_DATA = README AUTHORS INSTALL NEWS LICENSE ChangeLog 

#  install the man page
man_MANS=man/caprice32wx.1

all-local:
	@echo "=== all-local done ==="

clean-local: clean-doc
	@echo "=== clean-local done ==="

distclean-local: distclean-doc
	@echo "=== distclean-local done ==="

install-data-local: all-doc install-doc
	@echo "=== install-data-local done ==="

uninstall-local: uninstall-doc
	@echo "=== uninstall-local done ==="

if HAVE_DOXYGEN
all-doc:
	$(DOXYGEN) Doxyfile

clean-doc:
	rm -rf $(top_builddir)/doc

distclean-doc:
	rm -rf $(top_builddir)/doc

install-doc:
	$(mkdir_p) $(DESTDIR)$(docdir)
	cp -rf doc/html $(DESTDIR)$(docdir)

uninstall-doc:
	-rm -rf $(DESTDIR)$(docdir)/html
	-rmdir $(DESTDIR)$(docdir)
else
all-doc:
	@echo "*** WARNING! Doxygen is not available ***"; \
	echo "*** Documentation will not be built ***";

clean-doc:
	@echo "*** WARNING! Doxygen is not available ***"; \
	echo "*** Documentation will not be cleaned ***";

distclean-doc:
	@echo "*** WARNING! Doxygen is not available ***"; \
	echo "*** Documentation will not be cleaned ***";

install-doc:
	@echo "*** WARNING! Doxygen is not available ***"; \
	echo "*** Documentation will not be installed ***";

uninstall-doc:
	@echo "*** WARNING! Doxygen is not available ***"; \
	echo "*** Documentation will not be uninstalled ***";
endif

install-data-hook:
	@echo "Installing <<@PACKAGE@>> data files ..."; \
	mkdir -pv $(prefix)/share/@PACKAGE@; \
	cp -rvf rom $(prefix)/share/@PACKAGE@/; \
	echo ""; \
	echo "<<@PACKAGE@>> has ben installed on <<$(prefix)>> directory!"; \
	echo "You can execute <<caprice32wx>> now!"; \
	echo "";
