
MODULES_UT := Protocol.Interact.http.UT

$(MODULES_UT).SRC := \
			test.cpp \
			../HttpRequestParser.cpp \
			../HttpRequestPacker.cpp \
			../HttpResponsePacker.cpp \
			../HttpResponseParser.cpp \
			../../InteractResource.cpp \
		
 

$(MODULES_UT).INC := .


include $(BUILD_DIR)/Base.mk
