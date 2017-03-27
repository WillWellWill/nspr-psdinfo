

MODULE := Protocol.Interact.http

$(MODULE).SRC := \
			HttpRequestPacker.cpp \
			HttpRequestParser.cpp \
			HttpResponsePacker.cpp \
			HttpResponseParser.cpp
 

$(MODULE).INC := .


include $(BUILD_DIR)/Base.mk
