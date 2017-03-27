
MODULE := Protocol.Interact

$(MODULE).SRC := \
				InteractResource.cpp \
				MessageBuffer.cpp \
				InteractProtocolParser.cpp \
				InteractProtocolPacker.cpp \
				IConnectRequest.cpp \
				IOperationRequest.cpp \
				IDisconnectRequest.cpp \
				IConnectResponse.cpp \
				IOperationResponse.cpp \
				IDisconnectResponse.cpp \
				InteractNotify.cpp \
				IErrorResponse.cpp \
				InteractClient.cpp \
				InteractClientImp.cpp \
				InteractLiveSession.cpp \
				SessionDescription.cpp \


$(MODULE).INC := .

include $(BUILD_DIR)/Base.mk


