all:
	cd src && make

clean:
	cd src && make clean

archive: clean
	RELEASE=$$(cat release); \
	/bin/echo "  [TAR] ~/xprocmon-src-$$RELEASE.tar.gz"; \
	cd .. && \
	  tar czf ~/xprocmon-src-$$RELEASE.tar.gz \
	  --exclude=\.git xprocmon/
