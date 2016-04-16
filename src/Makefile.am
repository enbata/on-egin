bin_PROGRAMS = elkarte_gastronomikoa
elkarte_gastronomikoa_SOURCES = Pasahitza.c administratzailea.c aldatu.c \
	aukeraSartu.c aukerak.c bazkideak.c bestelakoak.c bodeganSartu.c bodegatikElkartera.c \
	elkarte_gastronomikoa.c elkartea.c faltak.c faltakEguneratu.c faltatikZenbat.c faltenGestioa.c \
	gaiBerriaSartu.c galdera.c gehiagoSartu.c hornitzaileak.c irten.c kendu.c kodea.c \
	konfigurazio_orokorra.c kontua.c kredituak.c modSarrera.c mugitu.c ordainketa.c \
	sarrera_aukera.c sartuGaia.c zenbatUnitate.c

# set the include path found by configure
INCLUDES = -I$(top_srcdir)/. -I$(top_srcdir)/src $(all_includes)

# the library search path.
elkarte_gastronomikoa_LDFLAGS = $(all_libraries) 
noinst_HEADERS = Pasahitza.h administratzailea.h aldatu.h aukeraSartu.h \
	aukerak.h bazkideak.h bestelakoak.h bodeganSartu.h bodegatikElkartera.h \
	elkartea.h faltak.h faltakEguneratu.h faltatikZenbat.h faltenGestioa.h \
	gaiBerriaSartu.h galdera.h gehiagoSartu.h hornitzaileak.h irten.h kendu.h kodea.h \
	konfigurazio_orokorra.h kontua.h kredituak.h mugitu.h ordainketa.h sarrera_aukera.h sartuGaia.h \
	zenbatUnitate.h
AM_CFLAGS = -O0 -g3 -lmysqlclient -lz -lnsl -lm `pkg-config --cflags gtk+-2.0`\
	\
		`pkg-config --libs gtk+-2.0`
