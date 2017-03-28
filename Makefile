
.PHONY: all clean rpm test workspace update install

TOP:=$(PWD)

NGINX_DIR_NAME:=nginx-1.10.2
NGINX_PATH=$(TOP)/Nginx/$(NGINX_DIR_NAME)
NGINX_BIN:=$(NGINX_PATH)/objs/nginx

NSPR_LIB:=$(TOP)/Nspr/Src/libpsdinfo.so

NGX_TEST_CONFIG:=$(NGINX_PATH)/objs/ngx_auto_headers.h

WORKSPACE:=$(TOP)/workspace

all: nginx psdinfo

nginx: psdinfo
	make -C $(NGINX_PATH)

psdinfo: $(NGX_TEST_CONFIG)
	make -C Nspr/Src

update:
	@rm -rf $(NGINX_BIN) $(NSPR_LIB)

workspace: update $(NGX_TEST_CONFIG) nginx workspace_install
	$(shell [ -z "$(shell pgrep PsdInfo)" ] || killall PsdInfo )
	cp $(NGINX_BIN) $(WORKSPACE)/sbin/PsdInfo
	$(WORKSPACE)/sbin/PsdInfo

$(NGX_TEST_CONFIG):
	cd $(NGINX_PATH); ./configure --prefix=$(WORKSPACE) --with-debug --add-module=../nginx-modules;

workspace_install: nginx
	$(shell [ -d $(WORKSPACE) ] || mkdir $(WORKSPACE))
	cd $(NGINX_PATH);make install
	$(shell [ -d ${HOME}/lib ] || mkdir ${HOME}/lib )
	cd ${HOME}/lib; ln -sf $(TOP)/Nspr/Src/libpsdinfo.so libpsdinfo.so
	cp -rf $(TOP)/Nspr/Html/* $(WORKSPACE)/html

clean:
	-cd $(NGINX_PATH);make clean
	-cd Nspr/Src; make clean
	-rm -rf $(WORKSPACE)
