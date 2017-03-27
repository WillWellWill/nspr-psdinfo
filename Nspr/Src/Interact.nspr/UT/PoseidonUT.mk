
MODULES_UT := Protocol.Interact.http.UT

$(MODULES_UT).SRC := \
			test.cpp \
			../InteractResource.cpp \
			../MessageBuffer.cpp \
			../InteractProtocolParser.cpp \
			../InteractProtocolPacker.cpp \
			../IConnectRequest.cpp \
			../IOperationRequest.cpp \
			../IDisconnectRequest.cpp \
			../IConnectResponse.cpp \
			../IOperationResponse.cpp \
			../IDisconnectResponse.cpp \
			../InteractNotify.cpp \
			../IErrorResponse.cpp \
			../InteractClient.cpp \
			../InteractClientImp.cpp \
			../InteractLiveSession.cpp \
		
 

$(MODULES_UT).INC := .


include $(BUILD_DIR)/Base.mk
