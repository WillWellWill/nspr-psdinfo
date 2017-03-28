
MODULE := Net

$(MODULE).SRC := \
				NsprAppCore.cpp \
				MsgConnection.cpp \
				StreamConnection.cpp \
				ApiDispatcher.cpp \
				WSConnection.cpp \
				StatisticsConnection.cpp \


$(MODULE).INC := .

include $(BUILD_DIR)/Base.mk


