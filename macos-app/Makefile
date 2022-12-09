
# ============================================================================
# FUNCTIONS

# $(call build_subproj,name)
define build_subproj
@echo "building $1 ..."
@cd $1 && bash build.sh
endef

# $(call clean_subproj,name)
define clean_subproj
@echo "removing $1/build ..."
@rm -rf $1/build
endef



# ============================================================================
# TARGETS

.PHONY: 00-osx-bundle 01-osx-bundle-fixup 02-osx-bundle-fixup2 03-osx-bundle-fixup3 04-osx-dylibbundler clean


all: clean 00-osx-bundle 01-osx-bundle-fixup 02-osx-bundle-fixup2 03-osx-bundle-fixup3 04-osx-dylibbundler

00-osx-bundle:
	$(call build_subproj,$@)

01-osx-bundle-fixup:
	$(call build_subproj,$@)

02-osx-bundle-fixup2:
	$(call build_subproj,$@)

03-osx-bundle-fixup3:
	$(call build_subproj,$@)

04-osx-dylibbundler:
	$(call build_subproj,$@)

clean:
	@echo "removing build directories..."
	@find . -type d -name build -mindepth 2 -prune -exec rm -rf {} \;
