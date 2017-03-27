
MODULE := Stream

$(MODULE).SRC := StreamProcFactory.cpp \
				 LogStreamProc.cpp \
				 StreamProc.cpp \


$(MODULE).INC := .

include $(BUILD_DIR)/Base.mk


